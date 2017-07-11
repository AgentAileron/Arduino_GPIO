/*  TFT Touchscreen test
 *  C: 11/07/2017 | LM: 11/07/2017
 *  ----------------------------------
 *  This sketch doubles as a documentation database for shield experiments
 *  
 *  > Diplay size in pixels: __X240
 *  > Screen coordinates aligned from top-right edge
 *  > Analog pins for display / touchscreen can be shared
 *  > Draw commands are static until screen reset or screen space overwritten with new command (allows pin sharing)
 *  ----------------------------------
 *  By Rithesh R Jayaram
 *  ----------------------------------
 *  Based on GPL tftPaint sketch
 *  Using modified Adafruit tft library
*/

// LIBRARIES //
#include <Adafruit_GFX.h>     // Core graphics library
#include <Adafruit_TFTLCD.h>  // Hardware-specific library
#include <TouchScreen.h>      // Touchscreen library

// INSTANTIATION //
/* Pressure precision based on plate resistance - default 300 ohms, verify w/ multimeter
Pins: XP, YP, XM, YM (ripped from original sketch definitions) */
TouchScreen ts = TouchScreen(A3, A2, 9, 8, 300); // Initialise Touchscreen (default w/ shield: A3, A2, 9, 8)

/* Pins: LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET (ripped from original sketch definitions) */
Adafruit_TFTLCD tft(A3, A2, A1, A0, A4);    // Initialise LCD Display (default w/shield: A3, A3, A1, A0, A4)


void setup(){
  Serial.begin(9600); // Debugging serial
  Serial.println(F("Debug sketch for TFT LCD 2.8\""));
  tft.reset();  // Resets tft device (instant white-screen is visual effect seen)

  checkDrivers(); // Prints found drivers to serial
}

void loop(){
  TSPoint p = ts.getPoint();  // Places touchscreen input values into tri-component var 'p'

  // shared touchscreen pins need to be made outputs (were being used as inputs for tft lcd)
  pinMode(A3, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(8, OUTPUT);
}


// Function to print device driver found to serial
void checkDrivers(void){
  uint16_t identifier = tft.readID();

  if(identifier == 0x9325) {
    Serial.println(F("Found ILI9325 LCD driver"));
  } else if(identifier == 0x9328) {
    Serial.println(F("Found ILI9328 LCD driver"));
  } else if(identifier == 0x7575) {
    Serial.println(F("Found HX8347G LCD driver"));
  } else if(identifier == 0x9341) {
    Serial.println(F("Found ILI9341 LCD driver"));
  } else if(identifier == 0x8357) {
    Serial.println(F("Found HX8357D LCD driver"));
  } else {
    Serial.print(F("Unknown LCD driver chip: "));
    Serial.println(identifier, HEX);
    return;
  }
}

