#include "Backflush.h"
#include "Button.h"
#include "Paddle.h"
#include "Circuit.h"
#include "Button.h"
#include "Display.h"
#include "Switch.h"
#include "Arduino.h"

extern Switch *m1;
extern Circuit *pump;
extern Button *button;
extern Display *display;


void Backflush::setFlowState(backflushFlowStates bstate) {

  if (bstate != flowState) {
    switch (bstate) {
      case STATE_REST:
        pump->disable(true);
        break;

      case STATE_FLOW:
        pump->enable(true);
        break;
    }
  }

  flowState = bstate;
}


void Backflush::startNextCycle() {
  
  state++;
  startTime = millis();
  counter = 0;
  
  if (state == B_CYCLE_1 || state == B_CYCLE_2 || state == B_CYCLE_3) {
    setFlowState(STATE_FLOW);
  }
  else {
    setFlowState(STATE_REST);
  }
}


int Backflush::getCycleNumber() {

  switch(state) {
    case B_CYCLE_1:
      return 1;
      
    case B_CYCLE_2:
      return 2;
      
    case B_CYCLE_3:
      return 3;
  }
  
  return 0;
}


void Backflush::displayRinse() {

  display->init(0);
  display->print(45, 30, "RINSE");
  display->print(25, 45, "PORTAFILTER");
  display->display();
}


void Backflush::displayInfo(int seconds, int flushSeconds, int restSeconds, int repeat) {

  display->init(0);
  display->print(5, 15, "CYCLE:");
  display->print(60, 15, "%.2d", getCycleNumber());
  display->print(80, 15, "/ %.2d", 3);
  display->print(5, 30, "ROUND:");
  display->print(60, 30, "%.2d", counter + 1);
  display->print(80, 30, "/ %.2d", repeat);
  display->print(5, 45, "FLOW:");
  display->print(60, 45, "%.2d", seconds >= flushSeconds ? flushSeconds : seconds);
  display->print(80, 45, "/ %.2d", flushSeconds);
  display->print(5, 60, "REST:");
  display->print(60, 60, "%.2d", seconds <= flushSeconds ? 0 : seconds - flushSeconds);
  display->print(80, 60, "/ %.2d", restSeconds);
  display->display();
}


void Backflush::updateState(int flushSeconds, int restSeconds, int repeat) {

  unsigned long now = millis();
  unsigned long seconds = (now - startTime) / 1000;

  displayInfo(seconds, flushSeconds, restSeconds, repeat);

  if (seconds >= (flushSeconds + restSeconds)) {
    counter++;
    if (counter >= repeat) {
      startNextCycle();
    }
    else {
      startTime = now;
      setFlowState(STATE_FLOW);
    }
  }
  else if (seconds >= flushSeconds) {
    setFlowState(STATE_REST);
  }
}


int Backflush::update() {

  // Cancel backflush
  if (state != B_CYCLE_CLEAN) {
    if (button->isPushed()) {
      state = B_CYCLE_END;
    }
  }

  switch(state) {
    case B_CYCLE_START:
      startNextCycle();
      break;

    case B_CYCLE_1:
      updateState(15, 30, 1);
      break;
      
    case B_CYCLE_2:
      updateState(5, 5, 5);
      break;

    case B_CYCLE_CLEAN:
      displayRinse();
      
      if (isPaddleOn()) {
        pump->enable();
      }
      else {
        pump->disable();
        if (button->isPushed()) {
          startNextCycle();    
        }   
      }
      
      break;
      
    case B_CYCLE_3:
      updateState(5, 5, 10);
      break;

    case B_CYCLE_END:
      setFlowState(STATE_REST);
      return 0;
  }

  return 1;
}


void Backflush::start() {
  
  state = B_CYCLE_START;
  startTime = millis();
  counter = 0;
  setFlowState(STATE_REST);
}
  

Backflush::Backflush() {

}

