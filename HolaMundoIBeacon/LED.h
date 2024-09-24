// -*- mode: c++ -*-

#ifndef LED_H_INCLUIDO
#define LED_H_INCLUIDO

/**
 * @file LED.h
 * @brief Definición de la clase LED para controlar un LED en un pin específico.
 * 
 * Este archivo contiene la implementación de la clase `LED` que permite controlar
 * el estado (encendido/apagado) de un LED conectado a un pin digital de un microcontrolador.
 * También incluye funciones para alternar el estado y hacer que el LED parpadee.
 */

/**
 * @brief Función auxiliar para pausar la ejecución por un tiempo determinado.
 * 
 * @param tiempo Duración de la pausa en milisegundos.
 */
void esperar(long tiempo) {
  delay(tiempo);
}

/**
 * @class LED
 * @brief Clase para controlar un LED conectado a un pin específico.
 * 
 * Esta clase permite encender, apagar, alternar y hacer brillar un LED
 * que está conectado a un pin digital del microcontrolador.
 */
class LED {
private:
  int numeroLED;    /**< Número del pin al que está conectado el LED. */
  bool encendido;   /**< Estado actual del LED (encendido = true, apagado = false). */

public:

  /**
   * @brief Constructor de la clase LED.
   * 
   * Inicializa el pin del LED y lo apaga por defecto.
   * 
   * @param numero Número del pin donde está conectado el LED.
   */
  LED(int numero)
    : numeroLED(numero), encendido(false)
  {
    pinMode(numeroLED, OUTPUT);
    apagar(); /**< Apaga el LED al inicializar. */
  }

  /**
   * @brief Enciende el LED.
   */
  void encender() {
    digitalWrite(numeroLED, HIGH); 
    encendido = true;
  }

  /**
   * @brief Apaga el LED.
   */
  void apagar() {
    digitalWrite(numeroLED, LOW);
    encendido = false;
  }

  /**
   * @brief Alterna el estado del LED.
   * 
   * Si el LED está encendido, lo apaga; si está apagado, lo enciende.
   */
  void alternar() {
    if (encendido) {
      apagar();
    } else {
      encender();
    }
  }

  /**
   * @brief Hace que el LED brille por un tiempo determinado.
   * 
   * Enciende el LED, espera el tiempo especificado, y luego lo apaga.
   * 
   * @param tiempo Tiempo en milisegundos durante el cual el LED estará encendido.
   */
  void brillar(long tiempo) {
    encender();
    esperar(tiempo);
    apagar();
  }
}; // class LED

#endif // LED_H_INCLUIDO
