/* main program for simulation on PC */

#include <iostream>
#include <unistd.h>

#ifndef SIMULATOR
#define SIMULATOR
#endif  /* SIMULATOR */

#include <core/Max7219.h>
#include <core/String5x7Buffer.h>

#define msleep(ms) usleep(ms * 1000)

void demo(const char *text) {
  Max7219_8x8_Simlator *dev = new Max7219_8x8_Simlator(8);

  String5x7Buffer *string5x7Buffer = new String5x7Buffer(8, text);

  while (string5x7Buffer->distToLeftSet() > 0) {
    dev->print(string5x7Buffer);
    string5x7Buffer->leftScroll(false);
    msleep(50);
  }
  msleep(300);

  while (string5x7Buffer->distToRightSet() > 0) {
    dev->print(string5x7Buffer);
    string5x7Buffer->leftScroll(false);
    msleep(50);
  }
  msleep(300);

  while (string5x7Buffer->distToAfter() > 0) {
    dev->print(string5x7Buffer);
    string5x7Buffer->leftScroll(false);
    msleep(50);
  }
  msleep(300);

  string5x7Buffer->reset();

  while (string5x7Buffer->distToCenter() > 0)
    string5x7Buffer->leftScroll(false);

  dev->print(string5x7Buffer);
  msleep(300);

  delete string5x7Buffer;
  delete dev;
}

int main(int argc, char *argv[]) {
  const char *text = "Hello!";
  if (argc > 1)
    text = argv[1];
  demo(text);

  return 0;
}
