#include <SPI.h>

struct Max7219_8x8 {
  unsigned char SS;
  unsigned char matrix_n;

  void init();
  void test();
  void sendToDevice(int addr, int data);
  void print(const unsigned char pattern[][4]);
};
