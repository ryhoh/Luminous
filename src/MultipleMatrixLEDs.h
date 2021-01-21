#ifndef _MULTIPLE_MATRIXLEDS_H_
#define _MULTIPLE_MATRIXLEDS_H_

#include "MatrixLED.h"

#define MultipleMatrixLED_MAX_LENGTH 64

/**
 * @brief LED panels in a row.
 * @note Supports mono-color, binary.
*/
typedef struct _MultipleMatrixLEDs {
  MatrixLED *matrixLEDs[MultipleMatrixLED_MAX_LENGTH];  ///< pointers to MatrixLED row.
  size_t length;  ///< valid length for matrixLEDs[].
  size_t each_length[MultipleMatrixLED_MAX_LENGTH];  ///< valid length for each matrixLEDs.
} MultipleMatrixLEDs;


#endif  /* _MULTIPLE_MATRIXLEDS_H_ */
