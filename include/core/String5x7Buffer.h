#ifndef _STRING5X7_H_
#define _STRING5X7_H_

#ifdef ARDUINO
#include <avr/pgmspace.h>
#endif

#ifdef SIMULATOR
#include <string.h>
#endif

#include "../Interface/DeviceAPI.h"
#include "MatrixBuffer.h"
#include "AsciiFonts.h"

class String5x7Buffer : public MatrixBuffer {
private:
  char *text;
  uint16_t len;  // includes '\0'

  // for scrolling
  int cur_in_chr = 0;
  int cur_text = 0;
  int shifted_line_n = 0;

  uint8_t toFont(char chr_num, int row_num);
  void insertOneColumnAtRightEnd(bool invert) override;

public:
  String5x7Buffer(short screen_n, const char *text);
  String5x7Buffer(const String5x7Buffer &) = delete;
  ~String5x7Buffer();
  void reset();

  // Behind state:      |-------|ABC
  int distToBehind();    // dist screen_right and text_left
  // LeftSet state:     |ABC----|
  int distToLeftSet();   // dist screen_left  and text_left
  // RightSet state:    |----ABC|
  int distToRightSet();  // dist screen_right and text_right
  // After state:    ABC|-------|
  int distToAfter();     // dist screen_left  and text_right
  // Center state:      |--ABC--|
  int distToCenter();    // dist to point (distToLeftSet + distToRightSet = 0)

  uint16_t getLen() { return this->len; }
};

#endif
