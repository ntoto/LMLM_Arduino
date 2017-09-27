#ifndef DISPLAY_ADAFRUIT_H_
#define DISPLAY_ADAFRUIT_H_

#include "Display.h"
#include <Adafruit_SSD1306.h>

class AdafruitDisplay : public Display {

  char * buffer;
  Adafruit_SSD1306 *lcd;


public:
  void init(int font);
  void print(int x, int y, const char *format, ...);
  void display();
  void reset();
  AdafruitDisplay();
};

#endif
