#include "Switch.h"
#include "Arduino.h"


unsigned int Switch::readPin() {

  if (isAnalog) {
    return analogRead(pin);
  }

  return digitalRead(pin);
}


bool Switch::isPushed() {

  unsigned int state = readPin();

  switch(type) {
    case NORMALLY_OPEN:
      return state == 0;

    case NORMALLY_CLOSED:
      return state != 0;
  }

  return false;
}

  
Switch::Switch(unsigned int pin, switchType type, bool isAnalog) {

  this->isAnalog = isAnalog;
  this->type = type;
  this->pin = pin;
  pinMode(pin, INPUT);
}


