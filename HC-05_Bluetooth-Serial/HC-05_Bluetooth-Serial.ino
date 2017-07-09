/*  Bluetooth Serial Communicator
 *  C: 09/07/2017 | LM: 09/07/2017
 *  ----------------------------------
 *  INCOMPLETE!
 *  ----------------------------------
 *  By Rithesh R Jayaram
 *  ----------------------------------
*/

// LIBRARIES //
#include <SoftwareSerial.h>// import the serial library

SoftwareSerial BTS(11, 10); // RX, TX
int ledpin=13;              // led on D13 will show blink on / off
long previousMillis = 0;    // will store last time LED was updated

long Counter=0;

void setup() {
  Serial.begin(9600);
  BTS.begin(9600);
  BTS.println("Module Initialising...");
  Serial.println("BT module now active");

  // AT MODE STUFF
  pinMode(8, INPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  if (BTS.available())
      Serial.println(BTS.read());
  if (Serial.available())
      BTS.write(Serial.read());

  if (digitalRead(8) == HIGH){
    digitalWrite(13, HIGH);
  }else if (digitalRead(8) == LOW){
    digitalWrite(13, LOW);
  }
      
  /*if(millis() - previousMillis > 1000) {
    previousMillis = millis();  
    Counter+=1;
  
    BTS.println(Counter); // Print to BT serial (not using usual TX/RX pins)
    Serial.println(Counter);
  }*/
}
