#include "include/LEDMatrix.h"
#include "include/String5x7Buffer.h"

Max7219_8x8 max7219_8x8;
String5x7Buffer *string5x7Buffer;

void setup(){
  max7219_8x8.LAT = 10;
  max7219_8x8.DAT = 11;
  max7219_8x8.CLK = 13;
  max7219_8x8.screen_n = 8;
  
  max7219_8x8.init();
  max7219_8x8.test();
  
  char text[] = "Hello wooooorld!";
  string5x7Buffer = new String5x7Buffer(8, text);
  delay(100);
}

void loop(){
  while (string5x7Buffer->distToLeftSet() > 0) {
    max7219_8x8.print(string5x7Buffer);
    string5x7Buffer->leftScroll(false);
    delay(100);
  }
  delay(500);

  while (string5x7Buffer->distToRightSet() > 0) {
    max7219_8x8.print(string5x7Buffer);
    string5x7Buffer->leftScroll(false);
    delay(100);
  }
  delay(500);

  while (string5x7Buffer->distToAfter() > 0) {
    max7219_8x8.print(string5x7Buffer);
    string5x7Buffer->leftScroll(false);
    delay(100);
  }
  delay(500);
  
  string5x7Buffer->reset();
//  string5x7Buffer->fill(false);
}
