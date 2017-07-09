/*  HMC5883L Diagnostic Sketch
 *  C: 09/07/2017 | LM: 09/07/2017
 *  ----------------------------------
 *  HMC883L PINS:
 *  SCL --> A4
 *  SDA --> A5
 *  ----------------------------------
 *  By Rithesh R Jayaram
 *  ----------------------------------
 *  Based on sketch by Kevin Townsend
 *  Using Adafruit HMC5883L Library
*/

// LIBRARIES //
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345); // Assign unique ID and instantiate compass instance

void setup() {
  
}

void loop() {
  
}
