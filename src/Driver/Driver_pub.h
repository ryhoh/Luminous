/**f_driver_pinMode
 * @file Driver_pub.h
 * @author ryhoh
 * @brief Driver層の公開ヘッダファイル
 * 
 */

#ifndef _DRIVER_PUB_H_
#define _DRIVER_PUB_H_

/* インクルード -----------------------------------------------*/
#include "internal\Driver.h"

/* 外部公開用関数 ---------------------------------------------*/
extern inline void f_driver_pinMode(uint8_t u8_pin, uint8_t u8_mode);
extern inline void f_driver_digitalWrite(uint8_t u8_pin, uint8_t u8_mode);
extern inline void f_driver_sleep(uint32_t u32_ms);
extern inline void f_driver_shiftOut(uint8_t u8_data, uint8_t u8_dat_pin, uint8_t u8_clk_pin, uint8_t u8_cs_pin);
extern inline void f_driver_shiftOuts(uint8_t u8_data, uint32_t u32_len, uint8_t u8_dat_pin, uint8_t u8_clk_pin, uint8_t u8_cs_pin);
extern inline void f_driver_timerInterrupt(void);
extern inline void f_driver_timerInterruptDisable(void);
extern inline void f_driver_timerInterruptEnable(void);

#endif  /* _DRIVER_PUB_H_ */
