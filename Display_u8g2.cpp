#include "Display_u8g2.h"

#include <U8g2lib.h>

#define BUFFER_SIZE 12


void U8g2Display::init(int font) {

  lcd->clearBuffer();
  
  if (font) {
    lcd->setFont(u8g2_font_freedoomr25_tn);
  }
  else {
  
    lcd->setFont(u8g2_font_freedoomr10_tu);
  } 
}


void U8g2Display::print(int x, int y, const char *format, ...) {

  va_list args;

  va_start (args, format);
  vsnprintf (buffer, BUFFER_SIZE, format, args);
  buffer[BUFFER_SIZE - 1] = '\0';
  
  lcd->setCursor(x,y);
  lcd->print(buffer);
}


void U8g2Display::display() {

  lcd->sendBuffer();
}


void U8g2Display::reset() {
  
  lcd->clearDisplay();
}


U8g2Display::U8g2Display() {

  buffer = (char *)malloc(BUFFER_SIZE);
  lcd = new U8G2_SSD1306_128X64_NONAME_F_HW_I2C(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ SCL, /* data=*/ SDA);
  lcd->begin();
  reset();
}

