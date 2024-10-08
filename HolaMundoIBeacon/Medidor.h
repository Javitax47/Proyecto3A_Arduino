// -*- mode: c++ -*-

#ifndef MEDIDOR_H_INCLUIDO
#define MEDIDOR_H_INCLUIDO

/**
 * @file Medidor.h
 * @brief Definición de la clase Medidor para medir ozono y temperatura.
 * 
 * Esta clase proporciona una interfaz para simular mediciones de ozono y temperatura
 * en un sistema. Los valores de medición están actualmente codificados.
 */

/**
 * @class Medidor
 * @brief Clase para simular la medición de ozono y temperatura.
 * 
 * Esta clase simula la medición de niveles de ozono y temperatura. En un sistema real,
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
   * @brief Medir el nivel de ozono.
   * 
   * Devuelve un valor simulado de la medición de ozono.
   * 
   * @return int Valor del nivel de ozono (simulado).
   */
  int medirozono() {
    // Read Vgas, Vref, and Vtemp
    float Vgas = analogRead(VgasPin) * (3.0 / 1023.0);  // Convert ADC value to voltage
    float Vref = analogRead(VrefPin) * (3.0 / 1023.0);  // Convert ADC value to voltage
    
    float Vgas0 = Voffset + Vref;

    // Calculate gas concentration (Ozone) in ppm
    float Cx = (Vgas - Vgas0) * (1/M);

    // Print the results
    // Print the results
    Serial.print("Vgas: "); Serial.println(Vgas, 4);
    Serial.print("Vref: "); Serial.println(Vref, 4);
    Serial.print("Ozone Concentration (ppm): "); Serial.println(Cx, 4);

    return Cx;
  }

  /**
   * @brief Medir la temperatura.
   * 
   * Devuelve un valor simulado de la medición de temperatura.
   * 
   * @return int Valor de la temperatura (simulado).
   */
  int medirTemperatura() {
    // Read Vtemp
    float Vtemp = analogRead(VtempPin) * (3.0 / 1023.0); // Convert ADC value to voltage, 1023 = 2^10 bits

    // Calculate temperature (°C)
    float temperature = (87.0 / 3) * Vtemp - 18.0;

    // Print the results
    Serial.print("Temperature (°C): "); Serial.println(temperature, 2);

    return temperature;
  }

}; // class Medidor

#endif // MEDIDOR_H_INCLUIDO
