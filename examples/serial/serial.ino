#include <DotMatrixLED.h>

#define ARDUINO

#define MATRIX_SIZE 12
#define WAIT 50

Max7219_8x8 *max7219_8x8;
String5x7Buffer *string5x7Buffer;

const int DIN = 11;
const int CS  = 10;
const int CLK = 13;

void setup(){
  Serial.begin(9600);
  
  max7219_8x8 = new Max7219_8x8(MATRIX_SIZE, DIN, CS, CLK);
  string5x7Buffer = new String5x7Buffer(MATRIX_SIZE, "Hello LEDMatrix!");
}

void loop(){
  while (string5x7Buffer->distToLeftSet() > 0) {
    max7219_8x8->print(string5x7Buffer);
    string5x7Buffer->leftScroll(false);
    delay(WAIT);
  }
  delay(500);

  while (string5x7Buffer->distToRightSet() > 0) {
    max7219_8x8->print(string5x7Buffer);
    string5x7Buffer->leftScroll(false);
    delay(WAIT);
  }
  delay(500);

  while (string5x7Buffer->distToAfter() > 0) {
    max7219_8x8->print(string5x7Buffer);
    string5x7Buffer->leftScroll(false);
    delay(WAIT);
  }
  delay(500);
  
  string5x7Buffer->reset();
//  string5x7Buffer->fill(false);

  if (Serial.available()) {
      delete string5x7Buffer;
      string5x7Buffer = NULL;
      string5x7Buffer = new String5x7Buffer(MATRIX_SIZE, Serial.readString().c_str());
  }
}
