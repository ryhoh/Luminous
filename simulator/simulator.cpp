/* main program for simulation on PC */

#include <iostream>
#include <unistd.h>

#define SIMULATOR
#define msleep(ms) usleep(ms * 1000)

#include "LEDMatrix.h"
#include "String5x7Buffer.h"

int main() {
  Max7219_8x8 dev;
  dev.screen_n = 8;

  char text[] = "Hello wooooorld!";
  String5x7Buffer *string5x7Buffer = new String5x7Buffer(8, text);

  while (string5x7Buffer->distToLeftSet() > 0) {
    dev.print(string5x7Buffer);
    string5x7Buffer->leftScroll(false);
    msleep(50);
  }
  msleep(300);

  while (string5x7Buffer->distToRightSet() > 0) {
    dev.print(string5x7Buffer);
    string5x7Buffer->leftScroll(false);
    msleep(50);
  }
  msleep(300);

  while (string5x7Buffer->distToAfter() > 0) {
    dev.print(string5x7Buffer);
    string5x7Buffer->leftScroll(false);
    msleep(50);
  }
  msleep(300);

  string5x7Buffer->reset();

  delete string5x7Buffer;
  return 0;
}
