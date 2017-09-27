#ifndef SWITCH_H
#define SWITCH_H

enum switchType {
  NORMALLY_OPEN,
  NORMALLY_CLOSED
};

class Switch {

  bool isAnalog;
  switchType type;
  unsigned int pin;

  unsigned int readPin();

public:
  bool isPushed();
  Switch(unsigned int pin, switchType type, bool isAnalog);
};

#endif
