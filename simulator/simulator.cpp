/* main program for simulation on PC */

#include <iostream>
#include <unistd.h>

#ifndef SIMULATOR
#define SIMULATOR
#endif  /* SIMULATOR */

#define msleep(ms) usleep(ms * 1000)

#include "../include/Max7219.h"
#include "../include/String5x7Buffer.h"

int main() {
  Max7219_8x8 *dev = new Max7219_8x8(8);

  char text[] = "Hello wooooorld!";
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

  delete string5x7Buffer;
  delete dev;
  return 0;
}
