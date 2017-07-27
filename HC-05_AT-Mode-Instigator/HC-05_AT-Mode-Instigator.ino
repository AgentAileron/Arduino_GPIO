/*  HC-05 Bluetooth Module AT Mode interrogator
 *  C: 27/07/2017 | LM: 27/07/2017
 *  ----------------------------------
 *  Activates and interacts with AT mode on BT module
 *  (Uses software serial to allow debug serial on 0,1 (UNO))
 *  
 *  BT serial = software serial to BT module
 *  Debug serial = serial to usual TX/RX (and debug monitor)
 *  
 *  To activate AT mode:
 *    
 *  ----------------------------------
 *  By Rithesh R Jayaram
 *  ----------------------------------
*/

// LIBRARIES //
#include <SoftwareSerial.h> // Software serial
SoftwareSerial BTS(11, 10); // RX | TX (secondary serial on these pins)

// VARS //
const long baudRate = 38400; 
boolean NL = true;
 
void setup() 
{
    Serial.begin(9600); // Initialise wired serial
    BTS.begin(baudRate); // Initialise BT serial
    Serial.print("BT serial started at "); Serial.println(baudRate);
    Serial.println(" baud");
}
 
void loop()
{
  btTransfer(); // 
}

// Reads and transfers data between debug and BT
void btTransfer(){
   char c;  // Holds temp char read in at each iteration

   // Write BT serial out to debug serial
    if (BTS.available()) {
        c = BTS.read();   // read in one byte
        Serial.write(c);  // write to debug serial
    }
 
 
    // Write debug serial out to BT serial
    if (Serial.available()) {
        c = Serial.read();  // read from debug
        BTS.write(c);       // write to BT
 
        // Echo the user input to the main window. The ">" character indicates the user entered text.
        if (NL) { Serial.print(">");  NL = false; }
        Serial.write(c);
        if (c == 10) { NL = true; } 
    }
 
}

