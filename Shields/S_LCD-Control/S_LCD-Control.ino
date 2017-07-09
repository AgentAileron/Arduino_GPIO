/*  RGB LCD CONTROL SKETCH
 *  C: 07/07/2017 | LM: 07/07/2017
 *  Rithesh Jayaram
*/

// LIBRARIES //
#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include <Adafruit_RGBLCDShield.h>
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();  // Initialise 1 lcd instance from Adafruit Library


// STATE VARIABLES // -- In button variable arrays, listed order is: Left, Right, Up, Down, Select
bool wasPress[5] = {false, false, false, false, false}; // Is true when button pressed during last cycle
bool bLight = true;                                 // Backlight state cannot be read - holds state of backlight
unsigned long regPress[5];                          // Holds time since button was pushed initially (milliseconds)


void setup() {
  Serial.begin(9600); // TODO: remove before making library (debug only)
  Serial.println("SERIAL IS ACTIVE");

  // Initialise lcd and enable backlight
  lcd.begin(16, 2); // (columns, rows)
  setBlight(true);
}

void loop() {
  checkButtons();
}




// PUT EVENT ACTIONS BELOW: //

// BUTTON PUSHED FUNCTIONS // --------------------------------
void btnUpPressed(void) {
  
}

// down
void btnDownPressed(void) {
  
}

// left
void btnLeftPressed(void) {

}

// right
void btnRightPressed(void) {

}

// select
void btnSelectPressed(void) {

}


// BUTTON RELEASED FUNCTIONS // --------------------------------
void btnUpReleased(void) {

}

// down
void btnDownReleased(void) {
  
}

// left
void btnLeftReleased(void) {

}

// right
void btnRightReleased(void) {

}

// select
void btnSelectReleased(void) {

}


/*  BUTTON HELD FUNCTION WRITING GUIDE:
 *   // For function to be called again once time since last run passes (Default) //
 *    void btn___Held(long timeSincePush) {
 *      if (timeSincePush > ###) {
 *        <FUNCTION STATEMENTS HERE>
 *        regPress[#] = millis();
 *      }
 *    }
 *
 *   // For function to only run once every press (Or use variable and trigger in btnPress statement)//
 *    void btn___Held(long timeSincePush) {
 *      if (timeSincePush > ###) {
 *        <FUNCTION STATEMENTS HERE>
 *        regPress[#] = 2147483647;
 *      }
 *    }
 */
// BUTTON HELD FUNCTIONS (can be multiple instances) //  ----
// up
void btnUpHeld(signed long timeSincePush) {
  if (timeSincePush > 5000) { // Replace 5000 with delay til held in milliseconds
    
    regPress[0] = millis();
  }
}

// down
void btnDownHeld(signed long timeSincePush) {
  if (timeSincePush > 5000) { // Replace 5000 with delay til held in milliseconds
    
    regPress[1] = 2147483647;
  }
}

// left
void btnLeftHeld(signed long timeSincePush) {
  if (timeSincePush > 5000) { // Replace 5000 with delay til held in milliseconds

    regPress[2] = millis();
  }
}

// right
void btnRightHeld(signed long timeSincePush) {
  if (timeSincePush > 5000) { // Replace 5000 with delay til held in milliseconds
    
    regPress[3] = millis();
  }
}

// select
void btnSelectHeld(signed long timeSincePush) {
  if (timeSincePush > 5000) { // Replace 5000 with delay til held in milliseconds
     
     regPress[4] = millis();
  }
}


// Function to check button states and trigger actions wehre applicable
void checkButtons(void) { // Function is fairly messy due to reference structure by libraries used
  uint8_t buttons = lcd.readButtons(); // Begins reading lcd module's button states
  // up
  if (buttons & BUTTON_UP) { // Button has been pressed this cycle
    if (wasPress[0]){ // Button held since last cycle
      btnUpHeld(millis() - regPress[0]);
    }else{ // Button has been held since last cycle
      btnUpPressed();
      regPress[0] = millis();
    }
    wasPress[0] = true;
  }else if (wasPress[0]){ // Button has been released since last cycle
    btnUpReleased();
    wasPress[0] = false;
  }
  
  // down
  if (buttons & BUTTON_DOWN) { // Button has been pressed this cycle
    if (wasPress[1]){ // Button held since last cycle
      btnDownHeld(millis() - regPress[1]);
    }else{ // Button has been held since last cycle
      btnDownPressed();
      regPress[1] = millis();
    }
    wasPress[1] = true;
  }else if (wasPress[1]){ // Button has been released since last cycle
    btnDownReleased();
    wasPress[1] = false;
  }
  
  // left
  if (buttons & BUTTON_LEFT) { // Button has been pressed this cycle
    if (wasPress[2]){ // Button held since last cycle
      btnLeftHeld(millis() - regPress[2]);
    }else{ // Button has been held since last cycle
      btnLeftPressed();
      regPress[2] = millis();
    }
    wasPress[2] = true;
  }else if (wasPress[2]){ // Button has been released since last cycle
    btnLeftReleased();
    wasPress[2] = false;
  }
  
  // right
  if (buttons & BUTTON_RIGHT) { // Button has been pressed this cycle
    if (wasPress[3]){ // Button held since last cycle
      btnRightHeld(millis() - regPress[3]);
    }else{ // Button has been held since last cycle
      btnRightPressed();
      regPress[3] = millis();
    }
    wasPress[3] = true;
  }else if (wasPress[3]){ // Button has been released since last cycle
    btnRightReleased();
    wasPress[3] = false;
  }
  
  // select
  if (buttons & BUTTON_SELECT) { // Button has been pressed this cycle
    if (wasPress[4]){ // Button held since last cycle
      btnSelectHeld(millis() - regPress[4]);
    }else{ // Button has been held since last cycle
      btnSelectPressed();
      regPress[4] = millis();
    }
    wasPress[4] = true;
  }else if (wasPress[4]){ // Button has been released since last cycle
    btnSelectReleased();
    wasPress[4] = false;
  }
}

// Function to toggle backlight - use instead of only hardware control - NB: only relevant for monocolour LCDs
void setBlight(bool setState) {
  bLight = setState;
  if (setState) {
    lcd.setBacklight(0x7);
  } else if (setState == false) {
    lcd.setBacklight(0x2);
  }
}

