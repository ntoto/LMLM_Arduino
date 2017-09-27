#include "Brew.h"
#include "Paddle.h"
#include "Switch.h"
#include "Circuit.h"
#include "Display.h"
#include "Arduino.h"

extern Switch *m1;
extern Switch *m2;
extern Circuit *solenoid;
extern Circuit *pump;
extern Display *display;


void Brew::displayshotTimer(unsigned char number) {

  display->init(1);
  display->print(45, 45, "%.2u", number);
  display->display();
}


void Brew::start() {
  
  startTime = millis();
  counter = 0;
  solenoid->enable();
  pump->enable();
}


int Brew::update() {
  
  unsigned long now = millis();

  if (isPaddleOn()) {
    counter = (now - startTime) / 1000;
    displayshotTimer(counter);
    if (m2->isPushed()) {
      solenoid->disable();
    }
    else {
      solenoid->enable();
    }
  }
  else {
    if (startTime != 0) {
      solenoid->disable();
      pump->disable();
      if ( counter <= 5 ||
           ( (((now - startTime) / 1000) - counter) > 2) ) {
            
        startTime = 0;
        counter = 0;
        return 0;
      }
    }
    
    if (counter > 0) {
      displayshotTimer(counter);
    }
  }

  return 1;
}


Brew::Brew() {
  
  startTime = 0;
  counter = 0;
}

