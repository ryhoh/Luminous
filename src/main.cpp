/**
 * @file main.cpp
 * @author ryhoh
 * @brief エントリポイントのソースファイル
 * 
 */

/* インクルード -----------------------------------------------*/
#define ARDUINO
#include <Arduino.h>

#include "Driver_pub.h"
#include "Middle_pub.h"
#include "App_pub.h"

void setup() {
  /* スタートアップタスク実行 */
}

void loop() {
    /* タスクスケジューラ実行 */
    /* TaskLED タスク開始 (16ms周期) */

    while (1) {
        /* タスクスケジューラ実行 */
        /* TaskInternet タスク開始 (80ms周期) */
    }
}
