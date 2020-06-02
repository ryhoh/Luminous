#ifndef _MATRIXUTILS_H_
#define _MATRIXUTILS_H_

#ifdef ARDUINO
#include <Arduino.h>

#elif defined SIMULATOR
#include <iostream>
using std::uint8_t;

#endif

#include "Interface/DeviceAPI.h"

/*
 *  list of error codes
 *
 *  0: MatrixUtils internal
 *  1: constructing
 *  2: allocating
 *
 */

namespace matrix_utils {
  void pError(unsigned int ecode);

  class TwoDimArray {
  protected:
    uint8_t *array;
    short axis0;
    short axis1;

  public:
    TwoDimArray(short axis0, short axis1);
    ~TwoDimArray();
    void setAt(short x, short y, uint8_t val);
    void setBitAt(short x, short y, uint8_t pointFromRight, bool val);
    uint8_t getAt(short x, short y);
  };
}

#endif
