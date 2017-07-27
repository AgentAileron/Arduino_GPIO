/*  HC-05 Bluetooth Module Basic Bluetooth Serial
 *  C: 27/07/2017 | LM: 27/07/2017
 *  ----------------------------------
 *  Communicates with bluetooth connected remote terminal
 *  to flash LED on / off
 *  ----------------------------------
 *  By Rithesh R Jayaram
 *  ----------------------------------
*/

// LIBRARIES //
#include <SoftwareSerial.h>// Serial Library (for software serial)

SoftwareSerial bt(10, 11); // RX, TX (On alternate AVR pins)
int btData; // Global var for number sent from pc

void setup() {
  bt.begin(9600);
  bt.println("Bluetooth On please press 1 or 0 blink LED ..");
  pinMode(13,OUTPUT);
}

void loop() {
  readBTSerial();
}


// Reads in from bt serial and operates onboard LED (pin 13)
void readBTSerial(void){
  while (bt.available()){ // Analogous to typical calls to Serial
    btData = bt.read();  // Read serial input into global var
    if (btData == '1'){ // -- '1' sent --
      digitalWrite(13, HIGH);
      bt.println("LED Activated");  // Print over BT serial
    } else if (btData == '0') { // -- '0' sent --
      digitalWrite(13, LOW);
      bt.println("LED DE-Activated");  // Print over BT serial
    }else{ // -- other input sent --
      bt.println("Invalid character! Use either '0' or '1'");
    }
  }
}

