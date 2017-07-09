/*  2.4 Inch TFT LCD Shield Diagnostic
 *  C: 09/07/2017 | LM: 09/07/2017
 *  ----------------------------------
 *  <Description>
 *  ----------------------------------
 *  By Rithesh R Jayaram
 *  ----------------------------------
 *  Using Adafruit TFT-LCD Library
*/

// LIBRARIES //
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
Adafruit_TFTLCD tft(A3, A2, A1, A0, A4);  // Initialise TFT-LCD instance

// COMMON COLOURS //
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

void setup() {
  
}

void loop() {
  
}
