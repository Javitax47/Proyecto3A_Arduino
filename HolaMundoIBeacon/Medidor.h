// -*- mode: c++ -*-

#ifndef MEDIDOR_H_INCLUIDO
#define MEDIDOR_H_INCLUIDO

/**
 * @file Medidor.h
 * @brief Definición de la clase Medidor para medir CO2 y temperatura.
 * 
 * Esta clase proporciona una interfaz para simular mediciones de CO2 y temperatura
 * en un sistema. Los valores de medición están actualmente codificados.
 */

/**
 * @class Medidor
 * @brief Clase para simular la medición de CO2 y temperatura.
 * 
 * Esta clase simula la medición de niveles de CO2 y temperatura. En un sistema real,
 * esta clase podría interactuar con sensores reales para obtener lecturas.
 */
class Medidor {

public:

  /**
   * @brief Constructor de la clase Medidor.
   * 
   * Inicializa el medidor. Actualmente, no realiza ninguna acción en el constructor.
   */
  Medidor() {
  }

  /**
   * @brief Método para iniciar el medidor.
   * 
   * Se utiliza para realizar cualquier configuración que no pueda hacerse
   * en el constructor. Actualmente no realiza ninguna acción.
   */
  void iniciarMedidor() {
    // Código de inicialización si es necesario en el futuro.
  }

  /**
   * @brief Medir el nivel de CO2.
   * 
   * Devuelve un valor simulado de la medición de CO2.
   * 
   * @return int Valor del nivel de CO2 (simulado).
   */
  int medirCO2() {
    return 235; /**< Valor simulado de CO2. */
  }

  /**
   * @brief Medir la temperatura.
   * 
   * Devuelve un valor simulado de la medición de temperatura.
   * 
   * @return int Valor de la temperatura (simulado).
   */
  int medirTemperatura() {
    return 12; /**< Valor simulado de temperatura. */
  }

}; // class Medidor

#endif // MEDIDOR_H_INCLUIDO
