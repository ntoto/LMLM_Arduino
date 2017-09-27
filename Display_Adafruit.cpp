#include "Display_Adafruit.h"

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
//#include <Fonts/FreeSans9pt7b.h>
//#include <Fonts/FreeSans24pt7b.h>
#include <Fonts/FreeUniversal9pt7b.h>
#include <Fonts/FreeUniversal24pt7b.h>
#include <Adafruit_SSD1306.h>


#define OLED_RESET 4
#define BUFFER_SIZE 12


void AdafruitDisplay::init(int font) {

  lcd->clearDisplay();
  
  if (font) {
    lcd->setFont(&FreeUniversal_Bold24pt7b);
  }
  else {
  
    lcd->setFont(&FreeUniversal_Regular9pt7b);
  }
  
  lcd->setTextSize(1);
  lcd->setTextColor(WHITE);
  
}


void AdafruitDisplay::print(int x, int y, const char *format, ...) {

  va_list args;

  va_start (args, format);
  vsnprintf (buffer, BUFFER_SIZE, format, args);
  buffer[BUFFER_SIZE - 1] = '\0';
  
  lcd->setCursor(x,y);
  lcd->print(buffer);
}


void AdafruitDisplay::display() {

  lcd->display();
}


void AdafruitDisplay::reset() {
  
  lcd->clearDisplay();
  lcd->display();
}


AdafruitDisplay::AdafruitDisplay() {

  buffer = (char *)malloc(BUFFER_SIZE);
  lcd = new Adafruit_SSD1306(OLED_RESET);
  lcd->begin(SSD1306_SWITCHCAPVCC, 0x3C);
  reset();
}

