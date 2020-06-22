#ifndef _STRING5X7_H_
#define _STRING5X7_H_

#ifdef ARDUINO
#include <avr/pgmspace.h>
#endif

#ifdef SIMULATOR
#include <string.h>
#endif

#include "../interface/DeviceAPI.h"
#include "../util/Typing.h"
#include "MatrixBuffer.h"
#include "AsciiFonts.h"

enum class Position {  // Decvice
  Behind,    //          |-------|ABC
  RightSet,  //          |----ABC|
  LeftSet,   //          |ABC----|
  After,     //       ABC|-------|
  Center,    //          |--ABC--|
};

class String5x7Buffer : public MatrixBuffer {
private:
  char *text;
  uint16_t len;  // includes '\0'

  // for scrolling
  uint16_t cur_in_chr = 0;
  uint16_t cur_text = 0;
  uint16_t shifted_line_n = 0;

  uint8_t toFont(char chr_num, int row_num);
  void insertOneColumnAtRightEnd(bool invert) override;

public:
  String5x7Buffer(uint16_t screen_n, const char *text);
  String5x7Buffer(const String5x7Buffer &) = delete;
  ~String5x7Buffer();

  void reset();
  int32_t distTo(Position pos);

  uint16_t getLen() { return this->len; }
};

#endif
