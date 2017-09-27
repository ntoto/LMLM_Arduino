#ifndef BUTTON_H_
#define BUTTON_H_

class Button {

  bool locked;
  unsigned int state;
  unsigned int pin;


public:
  bool isPushed();
  Button(unsigned int pin);
};

#endif
