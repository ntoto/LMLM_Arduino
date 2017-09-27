#ifndef DISPLAY_U8G2_H_
#define DISPLAY_U8G2_H_

#include "Display.h"
#include <U8g2lib.h>

class U8g2Display : public Display {

  char * buffer;
  U8G2_SSD1306_128X64_NONAME_F_HW_I2C *lcd;


public:
  void init(int font);
  void print(int x, int y, const char *format, ...);
  void display();
  void reset();
  U8g2Display();
};

#endif
