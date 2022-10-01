#ifndef _DRIVER_H_
#define _DRIVER_H_

#include <stdint.h>

#ifdef ARDUINO
#include <Arduino.h>
#endif

/* デバイスの差異を吸収する共通の関数群 */

/* -- Definition -- */
static inline void driv_call_pinMode(uint8_t pin, uint8_t INPUT_or_OUTPUT);
static inline void driv_call_digitalWrite(uint8_t pin, uint8_t HIGH_or_LOW);
static inline void driv_call_sleep(uint32_t ms);
static inline void driv_call_shiftOut(uint8_t data, uint8_t dat_pin, uint8_t clk_pin, uint8_t lat_pin);
/* -------------------- */

#ifdef ARDUINO

static void driv_call_pinMode(
  uint8_t pin,
  uint8_t INPUT_or_OUTPUT
) {
  pinMode(pin, INPUT_or_OUTPUT);
}

static inline void driv_call_digitalWrite(
  uint8_t pin,
  uint8_t HIGH_or_LOW
) {
  digitalWrite(pin, HIGH_or_LOW);
}

static inline void driv_call_sleep(
  uint32_t ms
) {
  delay(ms);
}

static inline void driv_call_shiftOut(
  uint8_t data,
  uint8_t dat_pin,
  uint8_t clk_pin,
  uint8_t lat_pin
) {
  shiftOut(data, dat_pin, clk_pin, lat_pin);
}

#endif  /* ARDUINO */

#endif  /* _DRIVER_H_ */
