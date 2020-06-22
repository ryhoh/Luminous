#include "../../include/util/MatrixUtils.h"

void matrix_utils::pError(uint8_t ecode) {
  #ifdef LED_BUILTIN
  const uint16_t ledPin = LED_BUILTIN;
  #else
  const uint16_t ledPin = 13;
  #endif

  pinMode(ledPin, OUTPUT);

  // for ecode == 0
  while (ecode == 0) {
    digitalWrite(ledPin, HIGH);
    delay(10000);
  }

  // for ecode >= 1
  while (true) {
    for (uint8_t i = 0; i < ecode; ++i) {
      digitalWrite(ledPin, HIGH);
      delay(50);
    }
    digitalWrite(ledPin, LOW);
    delay(1000);
  }
}

matrix_utils::TwoDimArray::TwoDimArray(uint16_t axis0, uint16_t axis1) {
  this->axis0 = axis0;
  this->axis1 = axis1;
  this->array = (uint8_t *)calloc(axis0 * axis1, sizeof(uint8_t));
  if (this->array == NULL) matrix_utils::pError(2);
}

matrix_utils::TwoDimArray::~TwoDimArray() {
  free(this->array);
}

void matrix_utils::TwoDimArray::setAt(uint16_t x, uint16_t y, uint8_t val) {
  this->array[x * this->axis1 + y] = val;
}

void matrix_utils::TwoDimArray::setBitAt(uint16_t x, uint16_t y, uint8_t pointFromRight, bool val) {
  if (pointFromRight > 7) return;

  if (val) this->array[x * this->axis1 + y] |= (0b1 << pointFromRight);
  else this->array[x * this->axis1 + y] &= ~(0b1 << pointFromRight);
}

uint8_t matrix_utils::TwoDimArray::getAt(uint16_t x, uint16_t y) {
  return this->array[x * this->axis1 + y];
}
