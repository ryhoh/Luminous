#ifndef STRING5X7_H
#define STRING5X7_H

#ifdef ARDUINO
#include <avr/pgmspace.h>
#endif

#include "MatrixBuffer.h"
#include "MatrixUtils.h"
#include "AsciiFonts.h"

class String5x7Buffer : public MatrixBuffer {
private:
  char *text;
  uint16_t len;

  // for scrolling
  int cur_in_chr = 0;
  int cur_text = 0;
  int shifted_line_n = 0;

  uint8_t toFont(char chr_num, int row_num);
  void insertOneColumnAtRightEnd(bool invert) override;

public:
  String5x7Buffer(short screen_n, char *text);
  String5x7Buffer(const String5x7Buffer &) = delete;
  ~String5x7Buffer();
  void reset();

  int distToBehind();    // dist screen_right and text_left
  int distToLeftSet();   // dist screen_left  and text_left
  int distToRightSet();  // dist screen_right and text_right
  int distToAfter();     // dist screen_left  and text_right
};

#endif
