// -*- mode: c++ -*-

#ifndef PUBLICADOR_H_INCLUIDO
#define PUBLICADOR_H_INCLUIDO

/**
 * @file Publicador.h
 * @brief Definición de la clase Publicador para emitir anuncios BLE de ozono y temperatura.
 * 
 * Esta clase utiliza una emisora BLE para emitir datos de ozono y temperatura mediante beacons iBeacon.
 * Los anuncios se envían con un formato específico que incluye un UUID, major y minor.
 */

/**
 * @class Publicador
 * @brief Clase para publicar mediciones de ozono y temperatura mediante BLE.
 * 
 * Esta clase permite emitir anuncios BLE con los valores medidos de ozono y temperatura.
 * Se utiliza la clase EmisoraBLE para manejar los anuncios de tipo iBeacon.
 */
class Publicador {

private:
  
  /**
   * @brief UUID del beacon utilizado para identificar el origen de los anuncios.
   */
  uint8_t beaconUUID[16] = { 
	'E', 'Q', 'U', 'I', 'P', 'O', '-', 'J', 
	'A', 'V', 'I', 'E', 'R', '-', '3', 'A'
	};

public:

  /**
   * @brief Emisora BLE que se encarga de realizar los anuncios.
   */
  EmisoraBLE laEmisora {
	"GTI-3A",   /**< Nombre de la emisora BLE. */
	0x004c,     /**< ID del fabricante (Apple). */
	4           /**< Potencia de transmisión (txPower). */
  };
  
  /**
   * @brief Nivel RSSI utilizado para los anuncios. Valor predeterminado.
   */
  const int RSSI = -53;

  /**
   * @enum MedicionesID
   * @brief Identificadores de tipo de medición para el campo major de iBeacon.
   * 
   * Estos valores se utilizan para distinguir entre distintos tipos de mediciones en los anuncios.
   */
  enum MedicionesID  {
	ozono = 11,         /**< Identificador de la medición de ozono. */
	TEMPERATURA = 12, /**< Identificador de la medición de temperatura. */
	RUIDO = 13        /**< Identificador de la medición de ruido (no implementado). */
  };

  /**
   * @brief Constructor de la clase Publicador.
   * 
   * Inicializa el publicador, pero no enciende la emisora BLE. La emisora debe encenderse explícitamente llamando a `encenderEmisora()`.
   */
  Publicador( ) {
	// No encender la emisora aquí. Debe hacerse en `encenderEmisora()`.
  }

  /**
   * @brief Enciende la emisora BLE.
   * 
   * Este método debe ser llamado desde el setup del sistema para iniciar la emisora BLE.
   */
  void encenderEmisora() {
	(*this).laEmisora.encenderEmisora();
  }

  /**
   * @brief Publica un valor de ozono mediante un anuncio iBeacon.
   * 
   * Emite un anuncio BLE con el valor de ozono especificado, incluyendo un contador para diferenciar anuncios.
   * 
   * @param valorozono Valor de la medición de ozono (minor).
   * @param contador Contador para identificar la secuencia de anuncios (parte del major).
   * @param tiempoEspera Tiempo de espera antes de detener el anuncio.
   */
  void publicarozono( int16_t valorozono, uint8_t contador, long tiempoEspera ) {
	uint16_t major = (MedicionesID::ozono << 8) + contador;
	(*this).laEmisora.emitirAnuncioIBeacon( (*this).beaconUUID, 
											major,
											valorozono, // minor
											(*this).RSSI // rssi
									);
	esperar( tiempoEspera );
	(*this).laEmisora.detenerAnuncio();
  }

  /**
   * @brief Publica un valor de temperatura mediante un anuncio iBeacon.
   * 
   * Emite un anuncio BLE con el valor de temperatura especificado, incluyendo un contador para diferenciar anuncios.
   * 
   * @param valorTemperatura Valor de la medición de temperatura (minor).
   * @param contador Contador para identificar la secuencia de anuncios (parte del major).
   * @param tiempoEspera Tiempo de espera antes de detener el anuncio.
   */
  void publicarTemperatura( int16_t valorTemperatura, uint8_t contador, long tiempoEspera ) {
	uint16_t major = (MedicionesID::TEMPERATURA << 8) + contador;
	(*this).laEmisora.emitirAnuncioIBeacon( (*this).beaconUUID, 
											major,
											valorTemperatura, // minor
											(*this).RSSI // rssi
									);
	esperar( tiempoEspera );
	(*this).laEmisora.detenerAnuncio();
  }
	
}; // class Publicador

#endif // PUBLICADOR_H_INCLUIDO
