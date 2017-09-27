#ifndef CIRCUIT_H_
#define CIRCUIT_H_

class Circuit {

  unsigned int state;
  unsigned int pin;

  bool controlSwitch;

public:
  bool isOn();
  void enable();
  void enable(bool override);
  void disable();
  void disable(bool override);
  Circuit(unsigned int pin, bool controlSwitch);
};

#endif
