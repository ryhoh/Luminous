#include "MatrixUtils.h"

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

unsigned char **matrix_utils::alloc2dimArray(short outer_size, short inner_size) {
  unsigned char **res = (unsigned char **)malloc(sizeof(unsigned char *) * outer_size);
  if (res == NULL) matrix_utils::pError(2);
  for (short i = 0; i < outer_size; ++i) {
    res[i] = (unsigned char *)calloc(inner_size, sizeof(unsigned char));
    if (res[i] == NULL) matrix_utils::pError(2);
  }

  return res;
}
