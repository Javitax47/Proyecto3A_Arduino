
// -*- mode: c++ -*-

#ifndef PUERTO_SERIE_H_INCLUIDO
#define PUERTO_SERIE_H_INCLUIDO

/**
 * @file PuertoSerie.h
 * @brief Definición de la clase PuertoSerie para la comunicación por puerto serie.
 * 
 * Esta clase facilita la comunicación a través del puerto serie. Permite inicializar el puerto a una velocidad específica y escribir mensajes.
 */

/**
 * @class PuertoSerie
 * @brief Clase para manejar la comunicación por puerto serie.
 * 
 * Esta clase permite inicializar la comunicación serie y escribir mensajes a través del puerto serie de manera sencilla.
 */
class PuertoSerie {

public:

  /**
   * @brief Constructor de la clase PuertoSerie.
   * 
   * Inicializa el puerto serie con la velocidad especificada en baudios.
   * 
   * @param baudios Velocidad en baudios para la comunicación serie.
   */
  PuertoSerie (long baudios) {
	Serial.begin( baudios );
	// Evitar usar el bloqueo de while (!Serial) para permitir un arranque fluido.
  }

  /**
   * @brief Espera un pequeño tiempo antes de que el puerto serie esté disponible.
   * 
   * Este método puede ser útil para esperar brevemente antes de operar con el puerto serie.
   */
  void esperarDisponible() {
	delay(10);   
  }

  /**
   * @brief Escribe un mensaje a través del puerto serie.
   * 
   * Este método utiliza plantillas para escribir cualquier tipo de dato compatible con `Serial.print()`.
   * 
   * @tparam T Tipo del mensaje a escribir.
   * @param mensaje El mensaje a escribir por el puerto serie.
   */
  template<typename T>
  void escribir (T mensaje) {
	Serial.print( mensaje );
  }
  
}; // class PuertoSerie

#endif // PUERTO_SERIE_H_INCLUIDO
