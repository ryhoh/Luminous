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
    initMatrixLED(matrixLEDs + i, 8, 8);

    (matrixLEDs + i)->buffer[0] = 0b00100100;
    (matrixLEDs + i)->buffer[1] = 0b01001001;
    (matrixLEDs + i)->buffer[2] = 0b10010010;
    (matrixLEDs + i)->buffer[3] = 0b00100100;
    (matrixLEDs + i)->buffer[4] = 0b01001001;
    (matrixLEDs + i)->buffer[5] = 0b10010010;
    (matrixLEDs + i)->buffer[6] = 0b00100100;
    (matrixLEDs + i)->buffer[7] = 0b01001001;
  }
}

void loop() {
  flushMatrixLEDsByMax7219(&max7219, matrixLEDs, 8);
  delay(1000);
  for (uint8_t i = 0; i < 8; ++i) {
    flipMatrixLED(matrixLEDs + i);
  }
}
