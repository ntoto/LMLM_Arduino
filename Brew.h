#ifndef BREW_H_
#define BREW_H_


class Brew {

  unsigned long startTime;
  unsigned int counter;
  unsigned int solenoidState;

  void displayshotTimer(unsigned char number);

public:
  Brew();
  void start();
  int update();
};

#endif
