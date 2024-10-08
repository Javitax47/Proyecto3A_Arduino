// -*-c++-*-

#include <bluefruit.h>

#undef min // Definiciones en bluefruit.h que colisionan con la biblioteca estándar
#undef max

/**
 * @file HolaMundoIBeacon.ino
 * @brief Implementación principal del programa que utiliza BLE para publicar datos de sensores.
 */

// --------------------------------------------------------------
#include "LED.h"
#include "PuertoSerie.h"

// --------------------------------------------------------------

// Define analog input pins
const int VgasPin = A5;   // Pin connected to Vgas
const int VrefPin = 28;   // Pin connected to Vref
const int VtempPin = 29;  // Pin connected to Vtemp

// Calibration constants
const int Voffset = 0;
const float TIA_GAIN = 499.0;   // Gain for the Ozone sensor
const float SENSITIVITY_CODE = 44.26;
const float M = SENSITIVITY_CODE * TIA_GAIN * 1e-9 * 1e3;  // Calibration factor for Ozone sensor

/**
 * @namespace Globales
 * @brief Contiene objetos globales para manejar el LED, la comunicación por puerto serie y otros módulos.
 */
namespace Globales {
  
  /**
   * @brief Objeto para controlar el LED conectado al pin 7.
   */
  LED elLED ( /* NUMERO DEL PIN LED = */ 7 );

  /**
   * @brief Objeto para gestionar la comunicación por puerto serie a 115200 baudios.
   */
  PuertoSerie elPuerto ( /* velocidad = */ 115200 );

  // Serial1 en el ejemplo de Curro creo que es la conexión placa-sensor
};

// --------------------------------------------------------------
#include "EmisoraBLE.h"
#include "Publicador.h"
#include "Medidor.h"

// --------------------------------------------------------------
namespace Globales {

  /**
   * @brief Objeto para manejar la publicación de datos vía BLE.
   */
  Publicador elPublicador;

  /**
   * @brief Objeto para gestionar las mediciones de ozono y temperatura.
   */
  Medidor elMedidor;

}; // namespace

// --------------------------------------------------------------

/**
 * @brief Inicializa la placa y sus módulos.
 * Actualmente no hace nada.
 */
void inicializarPlaquita () {
  // de momento nada
} // () 

// --------------------------------------------------------------

/**
 * @brief Función de configuración (setup).
 * Inicializa los módulos de comunicación, medición y publicación.
 * @dot
 * digraph setup {
 *   setup -> Globales::elPuerto.esperarDisponible;
 *   setup -> inicializarPlaquita;
 *   setup -> Globales::elPublicador.encenderEmisora;
 *   setup -> Globales::elMedidor.iniciarMedidor;
 *   setup -> esperar;
 *   setup -> Globales::elPuerto.escribir;
 * }
 * @enddot
 */
void setup() {
  Serial.begin(9600);
  // Initialize ADC pins
  pinMode(VgasPin, INPUT);
  pinMode(VrefPin, INPUT);
  pinMode(VtempPin, INPUT);

  Globales::elPuerto.esperarDisponible();

  inicializarPlaquita();

  // Allow the sensor to stabilize for an hour (calibration in clean air)
  Serial.println("Allowing sensor to stabilize...");
  //delay(3600000); // Wait for 1 hour
  delay(10000); // Wait for 10 seconds

  // Enciende la emisora BLE
  Globales::elPublicador.encenderEmisora();

  // Inicia el medidor de sensores
  Globales::elMedidor.iniciarMedidor();

  esperar( 1000 );

  Globales::elPuerto.escribir( "---- setup(): fin ---- \n " );
} // setup ()

// --------------------------------------------------------------

/**
 * @brief Realiza una secuencia de encendido y apagado del LED.
 * Utiliza tiempos de espera definidos entre cambios de estado.
 * @dot
 * digraph lucecitas {
 *   lucecitas -> Globales::elLED.brillar [label="100ms encendido"];
 *   lucecitas -> esperar [label="400ms"];
 *   lucecitas -> Globales::elLED.brillar [label="100ms encendido"];
 *   lucecitas -> esperar [label="400ms"];
 *   lucecitas -> Globales::elLED.brillar [label="100ms encendido"];
 *   lucecitas -> esperar [label="400ms"];
 *   lucecitas -> Globales::elLED.brillar [label="1000ms encendido"];
 *   lucecitas -> esperar [label="1000ms"];
 * }
 * @enddot
 */
inline void lucecitas() {
  using namespace Globales;

  elLED.brillar( 100 ); // 100 encendido
  esperar ( 400 ); //  400 apagado
  elLED.brillar( 100 ); // 100 encendido
  esperar ( 400 ); //  400 apagado
  Globales::elLED.brillar( 100 ); // 100 encendido
  esperar ( 400 ); //  400 apagado
  Globales::elLED.brillar( 1000 ); // 1000 encendido
  esperar ( 400 ); //  400 apagado
} // ()

// --------------------------------------------------------------

/**
 * @namespace Loop
 * @brief Espacio de nombres para variables del bucle principal.
 */
namespace Loop {
  uint8_t cont = 0; /**< Contador de iteraciones del loop. */
};

// --------------------------------------------------------------

/**
 * @brief Función principal (loop) del programa.
 * Ejecuta mediciones de ozono y temperatura, publica los datos vía BLE y maneja la emisión de un anuncio iBeacon.
 */
void loop () {

  using namespace Loop;
  using namespace Globales;

  cont++;

  elPuerto.escribir( "\n---- loop(): empieza " );
  elPuerto.escribir( cont );
  elPuerto.escribir( "\n" );

  // Secuencia de luces
  lucecitas();

  // Mide el valor de ozono y lo publica
  int valorozono = elMedidor.medirozono();
  
  elPublicador.publicarozono( valorozono,
							cont,
							1000 // intervalo de emisión
							);
  
  // Mide la temperatura y la publica
  int valorTemperatura = elMedidor.medirTemperatura();
  
  elPublicador.publicarTemperatura( valorTemperatura, 
									cont,
									1000 // intervalo de emisión
									);

  // Prueba de emisión iBeacon con datos personalizados
  char datos[21] = {
	'H', 'o', 'l', 'a',
	'H', 'o', 'l', 'a',
	'H', 'o', 'l', 'a',
	'H', 'o', 'l', 'a',
	'H', 'o', 'l', 'a',
	'H'
  };

  elPublicador.laEmisora.emitirAnuncioIBeaconLibre ( &datos[0], 21 );

  esperar( 100 );

  elPublicador.laEmisora.detenerAnuncio();

  elPuerto.escribir( "---- loop(): acaba **** " );
  elPuerto.escribir( cont );
  elPuerto.escribir( "\n" );
  
} // loop ()
