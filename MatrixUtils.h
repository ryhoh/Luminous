#ifndef MATRIXUTILS_H
#define MATRIXUTILS_H

#include <Arduino.h>

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
  uint8_t **alloc2dimArray(short outer_size, short inner_size);
  void free2dimArray(uint8_t **array, short outer_size);
}

#endif
