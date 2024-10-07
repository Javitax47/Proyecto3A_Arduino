#include "Wire.h"
#include <bluefruit.h>

// Define analog input pins
const int VgasPin = 5;   // Pin connected to Vgas
const int VrefPin = 28;   // Pin connected to Vref
const int VtempPin = 29;  // Pin connected to Vtemp

// Calibration constants
float Vgas0 = 0.0;        // Baseline voltage in clean air (to be set during calibration)
const float TIA_GAIN = 499.0;   // Gain for the Ozone sensor
const float M = 1 / (TIA_GAIN * 1e-9 * 1e3);  // Calibration factor for Ozone sensor

void setup() {
  Serial.begin(9600);
  // Initialize ADC pins
  pinMode(VgasPin, INPUT);
  pinMode(VrefPin, INPUT);
  pinMode(VtempPin, INPUT);

  // Allow the sensor to stabilize for an hour (calibration in clean air)
  Serial.println("Allowing sensor to stabilize...");
  delay(10000); // Wait for 1 hour
  
  // Read Vgas0 in clean air
  Vgas0 = analogRead(VgasPin) * (3.0 / 1023.0);  // Read and convert to voltage
  Serial.print("Vgas0 (Clean air baseline): ");
  Serial.println(Vgas0, 4);
}

void loop() {
  // Read Vgas, Vref, and Vtemp
  float Vgas = analogRead(VgasPin) * (3.0 / 1023.0);  // Convert ADC value to voltage
  float Vref = analogRead(VrefPin) * (3.0 / 1023.0);  // Convert ADC value to voltage
  float Vtemp = analogRead(VtempPin) * (3.0 / 1023.0); // Convert ADC value to voltage
  
  // Calculate gas concentration (Ozone) in ppm
  float Cx = (Vgas - Vgas0) * (1/M);

  // Calculate temperature (°C)
  float temperature = 87.0 * Vtemp - 18.0;

  // Print the results
  Serial.print("Vgas: "); Serial.println(Vgas, 4);
  Serial.print("Vref: "); Serial.println(Vref, 4);
  Serial.print("Vtemp: "); Serial.println(Vtemp, 4);
  Serial.print("Ozone Concentration (ppm): "); Serial.println(Cx, 4);
  Serial.print("Temperature (°C): "); Serial.println(temperature, 2);
  
  // Delay before next reading
  delay(500);  // Read every 2 seconds
}
