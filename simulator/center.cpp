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
  MatrixBuffer *blank = new MatrixBuffer(8);

  while (string5x7Buffer->distToCenter() > 0)
    string5x7Buffer->leftScroll(false);

  // Blinking at center
  dev->print(string5x7Buffer);
  msleep(300);

  dev->print(blank);
  msleep(300);

  dev->print(string5x7Buffer);
  msleep(300);

  dev->print(blank);
  msleep(300);

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
