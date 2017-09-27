#include "Button.h"
#include "Arduino.h"

bool Button::isPushed() {
  
  unsigned int currentState = digitalRead(pin) == 0;

  if (state && !locked) {
    locked = true;
    return true;
  }

  if (currentState != state) {
    state = currentState;
    locked = false;
  }

  return false;
}

  
Button::Button(unsigned int pin) {

  locked = false;
  state = 0;
  this->pin = pin;
  pinMode(pin, INPUT);
}


