#include <Arduino.h>

#include "DotMatrixLED.h"

Max7219 max7219(5, 4, 13, 0);
MatrixLED matrixLEDs[8];

void setup() {
  testRun(max7219);
  for (uint8_t i = 0; i < 8; ++i) {
    matrixLEDs[i] = MatrixLED(8, 8);
  }

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
  max7219.flushMatrixLEDs(matrixLEDs, 8);
  delay(1000);
  for (uint8_t i = 0; i < 8; ++i) {
    (matrixLEDs + i)->flip();
  }
}
