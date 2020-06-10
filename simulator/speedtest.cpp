/* main program for simulation on PC */

#include <iostream>
#include <unistd.h>
#include <chrono>
#include <thread>

#ifndef SIMULATOR
#define SIMULATOR
#endif  /* SIMULATOR */

#include <core/Max7219.h>
#include <core/String5x7Buffer.h>

#define msleep(ms) usleep(ms * 1000)

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::microseconds;

void demo(const char *text) {
  Max7219_8x8_Simlator *dev = new Max7219_8x8_Simlator(8);
  String5x7Buffer *string5x7Buffer = new String5x7Buffer(8, text);
  MatrixBuffer *blank = new MatrixBuffer(8);

  // スクロールにかかる時間の測定
  high_resolution_clock::time_point start = high_resolution_clock::now();

  while (string5x7Buffer->distToCenter() > 0)
    string5x7Buffer->leftScroll(false);
  
  high_resolution_clock::time_point end = high_resolution_clock::now();

  dev->print(string5x7Buffer);
  msleep(300);

  std::cout << "scrolling time: " << duration_cast<microseconds>(end - start).count() << "us" << std::endl;

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
