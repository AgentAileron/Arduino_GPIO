/*  TFT Touchscreen test
 *  C: 11/07/2017 | LM: 11/07/2017
 *  ----------------------------------
 *  <Description>
 *  ----------------------------------
 *  By Rithesh R Jayaram
 *  ----------------------------------
 *  Based on GPL tftPaint sketch
 *  Using modified Adafruit tft library
*/

// LIBRARIES //
include <Adafruit_GFX.h>      // Core graphics library
#include <Adafruit_TFTLCD.h>  // Hardware-specific library
#include <TouchScreen.h>      // Touchscreen library

// INSTANTIATION //
/* Pressure precision based on plate resistance - default 300 ohms, verify w/ multimeter
Pins: XP, YP, XM, YM (ripped from original sketch definitions) */
TouchScreen ts = TouchScreen(A3, A2, 9, 8, 300); // Initialise Touchscreen (default w/ shield: A3, A2, 9, 8)

/* Pins: LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET (ripped from original sketch definitions) */
Adafruit_TFTLCD tft(A3, A2, A1, A0, A4);    // Initialise LCD Display (default w/shield: A3, A3, A1, A0, A4)


void setup(){
  
}

void loop(){
  
}

