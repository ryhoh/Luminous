#include <Arduino.h>

extern "C" {
  #include "DotMatrixLED.h"
}

Max7219 max7219;
MatrixLED matrixLEDs[8];

void setup() {
  initMax7219(&max7219, 5, 4, 13, 0);
  testRunMax7219(&max7219);
  for (uint8_t i = 0; i < 8; ++i) {
    initMatrixLED(&matrixLEDs[i], 8, 8);
  }

  writeAsciisToMatrixLEDs(matrixLEDs, 7, "Hello!", 0);
}

void loop() {
  static uint8_t cnt = 0;
  fillMatrixLED(matrixLEDs + 7, false);
  writeAsciiToMatrixLED(matrixLEDs + 7, '0' + cnt, 1);
  flushMatrixLEDsByMax7219(&max7219, matrixLEDs, 8);
  
  delay(1000);

  if (cnt == 9) {
    cnt = 0;
  } else {
    ++cnt;
  }
}
