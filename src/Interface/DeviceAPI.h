#ifndef _DEVICEAPI_H_
#define _DEVICEAPI_H_

#ifdef SIMULATOR
#include <iostream>
using std::uint8_t;
#endif

/* デバイスの差異を吸収する共通の関数群 */

/* -- API Definition -- */
namespace DeviceAPI {
  static void call_pinMode(uint8_t pin, uint8_t INPUT_or_OUTPUT);
  static inline void call_digitalWrite(uint8_t pin, uint8_t HIGH_or_LOW);
  static inline void call_sleep(uint32_t ms);
  static inline void call_shiftOut(uint8_t data, uint8_t dat_pin, uint8_t clk_pin, uint8_t lat_pin);
};
/* -------------------- */

#ifdef ARDUINO
#include <Arduino.h>

void DeviceAPI::call_pinMode(uint8_t pin, uint8_t INPUT_or_OUTPUT) {
  pinMode(pin, INPUT_or_OUTPUT);
}

static inline void DeviceAPI::call_digitalWrite(uint8_t pin, uint8_t HIGH_or_LOW) {
  digitalWrite(pin, HIGH_or_LOW);
}

static inline void DeviceAPI::call_sleep(uint32_t ms) {
  delay(ms);
}

static inline void DeviceAPI::call_shiftOut(uint8_t data, uint8_t dat_pin, uint8_t clk_pin, uint8_t lat_pin) {
  shiftOut(data, dat_pin, clk_pin, lat_pin);
}

#endif  /* ARDUINO */


#ifdef SIMULATOR
#include <unistd.h>

// erase unnecessary constants/functions
#define OUTPUT 0
#define HIGH 0
#define LOW 0
#define MSBFIRST 0
#define digitalWrite(a, b)
#define pinMode(lat, HIGH_LOW)
#define delay(ms) sleep(ms * 1000)

static void DeviceAPI::call_pinMode(uint8_t pin, uint8_t INPUT_or_OUTPUT) {}
static inline void DeviceAPI::call_digitalWrite(uint8_t pin, uint8_t HIGH_or_LOW) {}
static inline void DeviceAPI::call_sleep(uint32_t ms) {}
static inline void DeviceAPI::call_shiftOut(uint8_t data, uint8_t dat_pin, uint8_t clk_pin, uint8_t lat_pin) {}

#endif  /* SIMULATOR */

#endif  /* _DEVICEAPI_H_ */
