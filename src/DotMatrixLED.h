#ifndef _DOTMATRIXLED_H_
#define _DOTMATRIXLED_H_

#if defined(__cplusplus)
extern "C" {
#endif

/* Buffers */
#include "MatrixLED.h"

/* Support functions for buffer */
#include "AsciiFont.h"
#include "JISFont.h"

/* Devices */
#ifndef SIMULATOR  // Can't use for simulation on terminal.
#include "LEDControllers.h"
#endif  /* SIMULATOR */

#if defined(__cplusplus)
}
#endif

#endif  /* _DOTMATRIXLED_H_ */
