#include <Arduino.h>

#include "DotMatrixLED.h"

Max7219 max7219(5, 4, 13, 0);
MatrixLED matrixLEDs[8];

void setup() {
  testRun(max7219);
  for (uint8_t i = 0; i < 8; ++i) {
    matrixLEDs[i] = MatrixLED(8, 8);
  }

  writeAsciisToMatrixLEDs(matrixLEDs, 7, "Hello!", 0);
}

void loop() {
  static uint8_t cnt = 0;
  (matrixLEDs + 7)->fill(false);
  writeAsciiToMatrixLED(matrixLEDs[7], '0' + cnt, 1);
  max7219.flushMatrixLEDs(matrixLEDs, 8);

  delay(1000);

  if (cnt == 9) {
    cnt = 0;
  } else {
    ++cnt;
  }
}
