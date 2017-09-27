#include <stdio.h>

#include "Paddle.h"
#include "Switch.h"
#include "Button.h"
#include "Circuit.h"
#include "Brew.h"
#include "Backflush.h"
#include "Display_u8g2.h"
#include "Display_Adafruit.h"


//#define SWITCH1_PIN A0
#define SWITCH1_PIN 4
#define SWITCH2_PIN 2
#define SOLENOID_PIN 8
#define PUMP_PIN 12
#define BUTTON_PIN 13


enum states {
  STATE_NONE,
  STATE_BREW,
  STATE_BACKFLUSH
};

enum states state;

Switch *m1 = NULL;
Switch *m2 = NULL;
Button *button = NULL;
Circuit *pump = NULL;
Circuit *solenoid = NULL;
Brew *brew = NULL;
Backflush *backflush = NULL;
Display *display = NULL;


void setup() {

  //display = new AdafruitDisplay();
  display = new U8g2Display();  

  m1 = new Switch(SWITCH1_PIN, NORMALLY_CLOSED, false);
  m2 = new Switch(SWITCH2_PIN, NORMALLY_OPEN, false);
  button = new Button(BUTTON_PIN);
  solenoid = new Circuit(SOLENOID_PIN, true);
  // Let the switch control the pump
  pump = new Circuit(PUMP_PIN, false);
  brew = new Brew();
  backflush = new Backflush();

  state = STATE_NONE;
}


void resetState() {
  
  display->reset();
  state = STATE_NONE;
}


void loop() {
  
  switch(state) {
    case STATE_BACKFLUSH:
      if (backflush->update() == 0) {
        resetState();
      }
      break;

    case STATE_BREW:
      if (brew->update() == 0) {
        resetState();
      }
      break;

    case STATE_NONE:
    default:
      if (button->isPushed()) {
        state = STATE_BACKFLUSH;
        backflush->start();
      }

      if (isPaddleOn()) {
        state = STATE_BREW;
        brew->start();
      }

      break;
  }

  delay(1);
}
