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

// VARIABLES //
// Holds parameters to be displayed (X, Y, Z, Degrees (else radians))
  bool valDisplay[4] = {false, false, false, true}; 
signed long coordStrength[3] = {0,0,0};  // Holds flux values read from magnetometer
unsigned long execTime; // Min time til next execution
bool coordprinted = false;  // True when any coordinates have been printed during a cycle
float declination = 0.2042; // Angle of declination at Melbourne Australia, 07/2017 (Radians)

void setup() {
  Serial.begin(9600);
  Serial.println("HMC5883L Magnetometer test now running:"); Serial.println();
  
  if(!mag.begin()){ // Function returns whether or not compass responded to activation command
      Serial.println("Error detecting HMC5883L - newline to retry...");
      while(1){ // Hangs sketch at this point until compass found + nl
        static int trialsMade = 0;
        if (Serial.read() == '\n'){
          if (mag.begin()){
            Serial.println("Sensor found!");
            break;
          }else{
            Serial.print("Error detecting HMC5883L - newline to retry... ("); Serial.print(trialsMade); 
                Serial.println(")");
            trialsMade++;
          }  
        }
      }
  execTime = millis();
  }
}

void loop() {
  if (millis() > execTime){
    for (int i=0;i < 3; i++){ // Print requeseted coordinate values
      static bool coordShown = false; // Is true when coordinate pre-statement is printed
      if (valDisplay[i]){
        coordprinted = true;
        if (!coordShown){ 
          Serial.print("Raw: ");
          coordShown = true;
        }
        // Print coordinate identifiers
        if (i == 0) Serial.print("x");
        else if (i == 1) Serial.print("y");
        else Serial.print("z");

        // Print coordinate
        Serial.print(coordStrength[i]); Serial.print(" ,");
      }
      coordShown = false; // Reset parameter
    }
    if (coordprinted){  // Add NL only if a coordinate was output
      Serial.println();
      coordprinted = false;
    }
    
    // Print Heading
    Serial.print("HDG: ");
    if (valDisplay[3]){ // Print in degrees
      Serial.print(readMagnetometer()*180/M_PI);
      Serial.println("°");
    }else{  // Print in radians
      Serial.print(readMagnetometer());
      Serial.println(" rads");
    }
    execTime = millis() + 200;  // Schedule next execution in 'x'ms
  }
}

// Function to read from sensor
float readMagnetometer(void){
  sensors_event_t event; 
  mag.getEvent(&event);       // Get event (I2C, save current x/y/z values
  coordStrength[0] = event.magnetic.x;
  coordStrength[1] = event.magnetic.y;
  coordStrength[2] = event.magnetic.z;
  
  float heading = atan2(coordStrength[1],coordStrength[0]); // Get TN heading in radians from X and Y
  // TODO - ADD Z CONSIDERATION CALCLATION HERE
  heading += declination; // Add/Deduct declination (convert magnetic to true bearing)
  if (heading < 0)    // Compensate if value too low
    heading += 2*PI;
  if (heading > 2*PI) // Compensate if value too high
    heading -= 2*PI;

  return(heading);  // Return heading in radians from true north
}

// Queries Serial for user input
void serialEvent(void){
  while(Serial.available()){
    static String inString = "";
    static bool takingDeclination = false;
    
    char inChar = (char)Serial.read();  // Read next byte from serial
    
    if (inChar == '\n'){  // When newline is given, execute command
      if (takingDeclination){  // Change inclination mode
        if (inString.toInt() > -PI){ // Valid declination value given
          if (inString.toInt() < PI)
            declination = inString.toInt();
        }else{ // Invalid declination value given
          Serial.println("Invalid declination value given! - must be in radians");
          takingDeclination = false;
        }
      }else if (inString.equalsIgnoreCase("degrees")){ // Set angular reading to degrees
        valDisplay[3] = true;
      }else if (inString.equalsIgnoreCase("radians")){ // Set angular reading to radians
        valDisplay[3] = false;
      }else if (inString.equalsIgnoreCase("changeinclination")
                    |inString.equalsIgnoreCase("change inclination")){ // change declination is requested
        takingDeclination = true;
        Serial.println("Submit new declination value now (radians");
      }else if (inString.equalsIgnoreCase("declination")){ // State current declination value
        Serial.print("Current Declination set to: ");Serial.print(declination);
          Serial.println(" Radians.");
      }else if (inString.equalsIgnoreCase("X")){  // Show/hide X val
        swapBool(valDisplay[0]);
      }else if (inString.equalsIgnoreCase("Y")){  // Show/hide Y val
        swapBool(valDisplay[1]);
      }else if (inString.equalsIgnoreCase("X")){  // Show/hide Z val
        swapBool(valDisplay[2]);
      }
      inString= ""; // Reset input string cache
    }else{ // Add current byte to input string
      inString += inChar;
    }
  }
}

// Function to toggle booleans
bool swapBool(bool inBool){
  if (inBool){
    inBool = false;
  }else{
    inBool = true;
  }
  return inBool;
}

