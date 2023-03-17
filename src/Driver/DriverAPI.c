/**
 * @file DriverAPI.c
 * @author ryhoh
 * @brief デバイスドライバの共通関数群
 * 
 */

/* インクルード -----------------------------------------------*/
#include "Driver\Common.h"
#include "Driver\DriverAPI.h"
#ifdef ARDUINO
#include <Arduino.h>
#endif

/* 関数定義 ---------------------------------------------------*/
/**
 * @brief ピンモード設定関数
 * 
 * @param u8_pin ピン番号
 * @param u8_mode ピンモード
 */
void f_driver_pinMode(uint8_t u8_pin, uint8_t u8_mode) {
#ifdef ARDUINO
  pinMode(u8_pin, u8_mode);
#else  /* ARDUINO */
#error "Arduino以外の環境では使用できません。"
#endif /* ARDUINO */
}

/**
 * @brief ピン出力関数
 * 
 * @param u8_pin ピン番号
 * @param u8_mode ピン出力値
 */
inline void f_driver_digitalWrite(uint8_t u8_pin, uint8_t u8_mode) {
#ifdef ARDUINO
  digitalWrite(u8_pin, u8_mode);
#else  /* ARDUINO */
#error "Arduino以外の環境では使用できません。"
#endif /* ARDUINO */
}

/**
 * @brief スリープ関数
 * 
 * @param u32_ms スリープ時間(ms)
 */
inline void f_driver_sleep(uint32_t u32_ms) {
#ifdef ARDUINO
  delay(u32_ms);
#else  /* ARDUINO */
#error "Arduino以外の環境では使用できません。"
#endif /* ARDUINO */
}

/**
 * @brief タイマ割り込み定義関数
 * 
 * @param u32_ms 割り込み実行周期(ms)
 */
inline void f_driver_timerInterrupt(void (*func)(void), uint32_t u32_ms) {
#ifdef ARDUINO
  // timer0_isr_init();
  // timer0_attachInterrupt(func);
  // timer0_write(ESP.getCycleCount() + u32_ms * 1000);
#else  /* ARDUINO */
#error "Arduino以外の環境では使用できません。"
#endif /* ARDUINO */
}

/**
 * @brief タイマ割り込み禁止関数
 * 
 */
inline void f_driver_timerInterruptDisable(void) {
#ifdef ARDUINO
  timer0_detachInterrupt();
#else  /* ARDUINO */
#error "Arduino以外の環境では使用できません。"
#endif /* ARDUINO */
}

/**
 * @brief タイマ割り込み許可関数
 * 
 */
inline void f_driver_timerInterruptEnable(void) {
#ifdef ARDUINO
  // timer0_attachInterrupt(timerInterrupt);
#else  /* ARDUINO */
#error "Arduino以外の環境では使用できません。"
#endif /* ARDUINO */
}

/**
 * @brief シフトレジスタ出力関数
 * 
 * @param u8_data 出力データ
 * @param u8_dat_pin データピン番号
 * @param u8_clk_pin クロックピン番号
 * @param u8_cs_pin チップセレクトピン番号
 */
inline void f_driver_shiftOut(
    uint8_t u8_data,
    uint8_t u8_dat_pin,
    uint8_t u8_clk_pin,
    uint8_t u8_cs_pin
) {   
    f_driver_digitalWrite(u8_cs_pin, m_LOW);
    for (uint8_t u8_i = 0; u8_i < 8; ++u8_i) {
        f_driver_digitalWrite(u8_clk_pin, m_LOW);
        f_driver_digitalWrite(u8_dat_pin, (u8_data & 0x80) ? m_HIGH : m_LOW);
        u8_data <<= 1;
        f_driver_digitalWrite(u8_clk_pin, m_HIGH);
    }
    f_driver_digitalWrite(u8_cs_pin, m_HIGH);
}

/**
 * @brief シフトレジスタ出力関数（配列）
 * 
 * @param u8_data 出力データ
 * @param u32_len 出力データ長
 * @param u8_dat_pin データピン番号
 * @param u8_clk_pin クロックピン番号
 * @param u8_cs_pin チップセレクトピン番号
 */
inline void f_driver_shiftOuts(
    const uint8_t u8_data[],
    uint32_t u32_len,
    uint8_t u8_dat_pin,
    uint8_t u8_clk_pin,
    uint8_t u8_cs_pin
) {
    f_driver_digitalWrite(u8_cs_pin, m_LOW);
    for (uint32_t u32_i = 0; u32_i < u32_len; ++u32_i) {
        uint8_t u8_byte = u8_data[u32_i];
        for (uint8_t u8_i = 0; u8_i < 8; ++u8_i) {
            f_driver_digitalWrite(u8_clk_pin, m_LOW);
            f_driver_digitalWrite(u8_dat_pin, (u8_byte & 0x80) ? m_HIGH : m_LOW);
            u8_byte <<= 1;
            f_driver_digitalWrite(u8_clk_pin, m_HIGH);
        }
    }
    f_driver_digitalWrite(u8_cs_pin, m_HIGH);
}
