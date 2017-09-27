#ifndef DISPLAY_H_
#define DISPLAY_H_

class Display {

public:
  virtual void init(int font) = 0;
  virtual void print(int x, int y, const char *format, ...) = 0;
  virtual void display() = 0;
  virtual void reset() = 0;
};

#endif
