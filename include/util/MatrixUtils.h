#ifndef _MATRIXUTILS_H_
#define _MATRIXUTILS_H_

#ifdef ARDUINO_ARCH_MATRIXLED
#include <Arduino.h>
#endif

#include "../interface/DeviceAPI.h"
#include "Typing.h"

/*
 *  list of error codes
 *
 *  0: MatrixUtils internal
 *  1: constructing
 *  2: allocating
 *
 */

namespace matrix_utils {
  void pError(uint8_t ecode);

  class TwoDimArray {
  protected:
    uint8_t *array;
    uint16_t axis0;
    uint16_t axis1;

  public:
    TwoDimArray(uint16_t axis0, uint16_t axis1);
    ~TwoDimArray();
    
    void setAt(uint16_t x, uint16_t y, uint8_t val);
    void setBitAt(uint16_t x, uint16_t y, uint8_t pointFromRight, bool val);
    uint8_t getAt(uint16_t x, uint16_t y);
  };
}

#endif
