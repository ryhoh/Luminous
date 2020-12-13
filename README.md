# DotMatrix-LED Library

Library for printing char or string on LED-Matrix.  

Avaiable on arduino projects.  
(Arduino, ESP8266, ...)

## Supported LED Drivers

- Max7219

## Usage

### On Arduino Project

The library is written in C. Use `extern "C"`.

<figure style="text-align:center;">
	<img src="resources/led_example.jpg", width=720px>
	<figcaption>Simulation on terminal</figcaption>
</figure>

- Clock sketch for ESP8266

> sample/esp8266_time2/esp8266_time2.ino

```cpp
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <time.h>

extern "C" {
  #include "DotMatrixLED.h"
}

const String WIFI_SSID = "your_ssid";
const String WIFI_PASSWORD = "your_password";

Max7219 max7219;
MatrixLED matrixLEDs[8];

void setup() {
  pinMode(4, OUTPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while(WiFi.status() != WL_CONNECTED) {
    digitalWrite(4, HIGH);
    delay(100);
    digitalWrite(4, LOW);
    delay(500);
  }
  configTzTime("JST-9", "ntp.nict.jp", "ntp.jst.mfeed.ad.jp");
  
  initMax7219(&max7219, 5, 4, 13, 3);
  testRunMax7219(&max7219);
  for (uint8_t i = 0; i < 8; ++i) {
    initMatrixLED(&matrixLEDs[i], 8, 8);
  }

  writeJISsToMatrixLEDs(matrixLEDs, 3, "現在 ", 0);
  flushMatrixLEDsByMax7219(&max7219, matrixLEDs, 8);
}

void loop() {
  static time_t t;
  static struct tm *tm;
  static char now_s[] = "12:34:56";
  
  t = time(NULL);
  tm = localtime(&t);
  now_s[0] = '0' + tm->tm_hour / 10;
  now_s[1] = '0' + tm->tm_hour % 10;
  now_s[3] = '0' + tm->tm_min / 10;
  now_s[4] = '0' + tm->tm_min % 10;
  now_s[6] = '0' + tm->tm_sec / 10;
  now_s[7] = '0' + tm->tm_sec % 10;

  fillMatrixLED(matrixLEDs + 3, false);
  fillMatrixLED(matrixLEDs + 4, false);
  fillMatrixLED(matrixLEDs + 5, false);
  fillMatrixLED(matrixLEDs + 6, false);
  fillMatrixLED(matrixLEDs + 7, false);
  writeJISsToMatrixLEDs(matrixLEDs + 2, 6, now_s, 1);
  flushMatrixLEDsByMax7219(&max7219, matrixLEDs, 8);

  delay(1000);
}
```

- Simple sketch for Arduino

> sample/ascii/ascii.ino

```cpp
#include <Arduino.h>

extern "C" {
  #include "DotMatrixLED.h"
}

Max7219 max7219;          // module
MatrixLED matrixLEDs[8];  // panel

void setup() {
  /* init module */
  initMax7219(&max7219, 5, 4, 13, 0);
  testRunMax7219(&max7219);
  
  /* init panel */
  for (uint8_t i = 0; i < 8; ++i) {
    initMatrixLED(&matrixLEDs[i], 8, 8);
  }

  /* write to module */
  writeAsciisToMatrixLEDs(matrixLEDs, 7, "Hello!", 0);
}

void loop() {
  static uint8_t cnt = 0;
  fillMatrixLED(matrixLEDs + 7, false);
  writeAsciiToMatrixLED(matrixLEDs + 7, '0' + cnt, 1);
  flushMatrixLEDsByMax7219(&max7219, matrixLEDs, 8);

  delay(1000);

  if (cnt == 9) {
    cnt = 0;
  } else {
    ++cnt;
  }
}

```


### On Terminal (Simulation)

You can print MatrixLED to stdout.

<figure style="text-align:center;">
	<img src="resources/std_example.png", width=720px>
	<figcaption>Simulation on terminal</figcaption>
</figure>

```c:simulator/simulator.c
#include <stdio.h>
#include <stdint.h>
#include "DotMatrixLED.h"

const uint8_t matrix_length = 4;
const uint8_t height = 8;
const uint8_t width = 8;
const char on[]  = "●";
const char off[] = "○";

int main(int argc, char **argv) {
  const char *target = (argv[1] == NULL) ? "Hello" : argv[1];
  
  MatrixLED matrixLEDs[matrix_length];
  for (uint8_t i = 0; i < matrix_length; ++i) {
    initMatrixLED(&matrixLEDs[i], height, width);
  }

  writeJISsToMatrixLEDs(matrixLEDs, matrix_length, target, 0);

  for (uint8_t row_i = 0; row_i < height; ++row_i) {
    for (uint8_t matrix_i = 0; matrix_i < matrix_length; ++matrix_i) {
      uint8_t row = *((matrixLEDs + matrix_i)->buffer + row_i);
      for (uint8_t bit_i = 0; bit_i < 8; ++bit_i)
        printf("%s", (row >> (7 - bit_i) & 0b1) ? on : off);
    }
    printf("\n");
  }
}
```

## Data structure
### MatrixLED.h

```c
typedef struct _MatrixLED {
  uint8_t width;   // width  <= 8
  uint8_t height;  // height <= 8
  uint8_t buffer[8];  // 8*8 bit = 64 bit = 8 byte
} MatrixLED;
```
One MatrixLED represents one matrix panel.

<figure style="text-align:center;">
	<img src="resources/dot-matrix-8x8.jpg", width=240px>
	<figcaption>Matrix panel (8x8)</figcaption>
</figure>

--

shirosha2 Dec. 2020