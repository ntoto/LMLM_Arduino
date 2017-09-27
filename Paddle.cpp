#include "Paddle.h"
#include "Switch.h"

extern Switch *m1;

bool isPaddleOn() {
  
  return m1->isPushed() == false;
}
