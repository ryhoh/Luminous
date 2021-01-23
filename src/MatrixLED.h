#ifndef _MATRIXLED_H_
#define _MATRIXLED_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/* --------- */
/* MatrixLED */
/* --------- */

/**
 * @brief Buffer for matrix LED panel.
 * @note Supports mono-color, binary and up to 8x8 size panel.
*/
struct MatrixLED {
  uint8_t width;   ///< width  <= 8
  uint8_t height;  ///< height <= 8
  uint8_t buffer[8];  ///< 8*8 bit = 64 bit = 8 byte

  /**
   * @brief Initialize MatrixLED.
   * @param matrixLED [in] Pointer of MatrixLED to initialize.
   * @note The width and height is 0.
  */
  MatrixLED(): width(0), height(0) {}

  /**
   * @brief Initialize MatrixLED.
   * @param matrixLED [in] Pointer of MatrixLED to initialize.
   * @param width [in] Number of LED on the panel (horizontal).
   * @param height [in] Number of LED on the panel (vertical).
   * @note It fails when the panel is larger than 8x8 and set 0 to width and height.
  */
  MatrixLED(uint8_t width, uint8_t height);

  /**
   * @brief Destroy MatrixLED.
  */
  ~MatrixLED() {}

  /**
   * @brief Invert all LEDs' state (on or off).
  */
  void flip();

  /**
   * @brief Fill all LEDs with 0 or 1.
   * @param value [in] Value for filling (0 or 1).
  */
  void fill(bool value);

  /**
   * @brief Shift all LEDs to left by one bit.
   * @param padding [in] Bits for inserting right end.
   * @retval uint8_t Pack of overflowed bits
  */
  uint8_t leftShift(uint8_t padding);
};


// /* -------------- */
// /* MatrixLEDArray */
// /* -------------- */

// /**
//  * @brief Array of MatrixLED modules.
//  * @note Supports mono-color, binary.
// */
// struct MatrixLEDArray {
//   MatrixLED *matrixLEDs;
//   size_t length;  ///< valid length of matrixLEDs.

//   /**
//    * @brief Initialize MatrixLEDArray.
//    * @param matrixLEDs [in] Pointer to an Array of MatrixLED.
//    * @param length [in] valid length of matrixLEDs.
//    * @retval MatrixLEDArray Given MatrixLEDArray pointer on success
//   */
//   MatrixLEDArray(MatrixLED *matrixLEDs, size_t length);

//   /**
//    * @brief Destroy MatrixLEDArray
//   */
//  ~MatrixLEDArray() {}

//   /**
//    * @brief Invert all LEDs' state (on or off).
//   */
//   void flip();

//   /**
//    * @brief Fill all LEDs with 0 or 1.
//    * @param value [in] Value for filling (0 or 1).
//   */
//   void fill(bool value);

//   /**
//    * @brief Shift all LEDs to left by one bit.
//    * @retval uint8_t Pack of overflowed bits
//   */
//   uint8_t leftShift(uint8_t padding);
// };

// /* ------------------ */
// /* MultipleMatrixLEDs */
// /* ------------------ */

// /**
//  * @brief Rows of LED panel arrays.
//  * @note Supports mono-color, binary.
// */
// typedef struct _MultipleMatrixLEDArray {
//   MatrixLEDArray *matrixLEDArray;  ///< pointers to Array of MatrixLEDArray.
//   size_t length;  ///< valid length
// } MultipleMatrixLEDArray;

// /**
//  * @brief Initialize MultipleMatrixLEDArray.
//  * @param multipleMatrixLEDArray [in] Pointer to MultipleMatrixLEDArray to initialize.
//  * @param matrixLEDArray [in] Pointer to an Array of MatrixLEDArray.
//  * @param matrixLEDs [in] Pointer to 2d Array of MatrixLED.
//  * @param col_length [in] Number of MatrixLEDArray (horizontal).
//  * @param row_length [in] Number of MatrixLEDArray (vertical).
//  * @param width [in] Number of LED per one panel (horizontal).
//  * @param height [in] Number of LED per one panel (vertical).
//  * @retval MatrixLEDArray Given MatrixLEDArray pointer on success
//  * @retval NULL on fail
//  * @note It fails when the each panel is larger than 8x8.
// */
// MultipleMatrixLEDArray *initMultipleMatrixLEDArray(MultipleMatrixLEDArray *multipleMatrixLEDArray, MatrixLEDArray *matrixLEDArray, MatrixLED **matrixLEDs, size_t col_length, size_t row_length, uint8_t width, uint8_t height);

#endif  /* _MATRIXLED_H_ */
