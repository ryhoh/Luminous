#ifndef _DOTMATRIXLED_H_
#define _DOTMATRIXLED_H_

#ifdef ARDUINO
extern "C" {
#endif

/* Buffers */
#include "MatrixLED.h"

/* Support functions for buffer */
#include "AsciiMatrix.h"
#include "JISMatrix.h"

/* Devices */
#ifndef SIMULATOR  // Can't use for simulation on terminal.
#include "LEDControllers.h"
#endif  /* SIMULATOR */

#ifdef ARDUINO
}
#endif

#endif  /* _DOTMATRIXLED_H_ */
