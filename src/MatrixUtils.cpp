#include "../include/MatrixUtils.h"

#ifdef SIMULATOR
#include <unistd.h>
#define delay(ms) sleep(ms * 1000)

// -- erase unnecessary variables/function
#define HIGH
#define LOW
#define OUTPUT
#define digitalWrite(a, b)
#define pinMode(a, b)
// --

#endif

void matrix_utils::pError(unsigned int ecode) {
  const static int built_in_LED = 13;
  pinMode(built_in_LED, OUTPUT);

  // for ecode == 0
  while (ecode == 0) {
    digitalWrite(built_in_LED, HIGH);
    delay(10000);
  }

  // for ecode >= 1
  while (true) {
    for (unsigned int i = 0; i < ecode; ++i) {
      digitalWrite(built_in_LED, HIGH);
      delay(50);
    }
    digitalWrite(built_in_LED, LOW);
    delay(1000);
  }
}

matrix_utils::TwoDimArray::TwoDimArray(short axis0, short axis1) {
  this->axis0 = axis0;
  this->axis1 = axis1;
  this->array = (uint8_t *)calloc(axis0 * axis1, sizeof(uint8_t));
  if (this->array == NULL) matrix_utils::pError(2);
}

matrix_utils::TwoDimArray::~TwoDimArray() {
  free(this->array);
}

void matrix_utils::TwoDimArray::setAt(short x, short y, uint8_t val) {
  this->array[x * this->axis1 + y] = val;
}

void matrix_utils::TwoDimArray::setBitAt(short x, short y, uint8_t pointFromRight, bool val) {
  if (pointFromRight > 7) return;

  if (val) this->array[x * this->axis1 + y] |= (0b1 << pointFromRight);
  else this->array[x * this->axis1 + y] &= ~(0b1 << pointFromRight);
}

uint8_t matrix_utils::TwoDimArray::getAt(short x, short y) {
  return this->array[x * this->axis1 + y];
}
