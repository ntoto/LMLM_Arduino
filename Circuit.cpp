#include "Circuit.h"
#include "Arduino.h"


Circuit::Circuit(unsigned int pin, bool controlSwitch) {

  state = 0;
  this->controlSwitch = controlSwitch;
  this->pin = pin;
  pinMode(pin, OUTPUT);

  if (controlSwitch) {
    digitalWrite(pin, LOW);
  }
}


bool Circuit::isOn() {

  return state == 1;
}


void Circuit::enable(bool override) {

  if (!state && (controlSwitch || override)) {
    digitalWrite(pin, HIGH);
  }

  state = 1;
}


void Circuit::enable() {

  enable(false);
}


void Circuit::disable(bool override) {
  
  if (state && (controlSwitch || override)) {
    digitalWrite(pin, LOW);
  }

  state = 0;
}


void Circuit::disable() {

  disable(false);
}



