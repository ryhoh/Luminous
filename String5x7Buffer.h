#ifndef STRING5X7_H
#define STRING5X7_H

#include "MatrixBuffer.h"
#include "MatrixUtils.h"

class String5x7Buffer : public MatrixBuffer {
private:
  // access as "_fonts['a' - OFFSET]"
  static const int OFFSET = 0x20;
  static uint8_t _fonts[95][7];
  char *text;
//  char *text_bak;

  // for scrolling
  int cur_in_chr = 0;
  int cur_text = 0;
  
  uint8_t toFont(char chr_num, int row_num);
  void insertOneColumnAtRightEnd(bool invert) override;

public:
  String5x7Buffer(short screen_n, char *text);
  ~String5x7Buffer();
//  void leftScroll(bool invert) override;
  void reset();
};

#endif
