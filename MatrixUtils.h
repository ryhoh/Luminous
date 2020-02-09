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
  unsigned char **alloc2dimArray(short outer_size, short inner_size);
}

#endif
