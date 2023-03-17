/**
 * @file DriverAPI.h
 * @author ryhoh
 * @brief デバイスドライバの共通関数群
 * 
 */

#ifndef _DRIVERAPI_H_
#define _DRIVERAPI_H_

/* インクルード -----------------------------------------------*/
#include "Common.h"

/* 外部関数のプロトタイプ --------------------------------------*/
inline void f_driver_pinMode(uint8_t u8_pin, uint8_t u8_mode);
inline void f_driver_digitalWrite(uint8_t u8_pin, uint8_t u8_mode);
inline void f_driver_sleep(uint32_t u32_ms);
inline void f_driver_shiftOut(uint8_t u8_data, uint8_t u8_dat_pin, uint8_t u8_clk_pin, uint8_t u8_cs_pin);
inline void f_driver_shiftOuts(uint8_t u8_data, uint32_t u32_len, uint8_t u8_dat_pin, uint8_t u8_clk_pin, uint8_t u8_cs_pin);
inline void f_driver_timerInterrupt(void);
inline void f_driver_timerInterruptDisable(void);
inline void f_driver_timerInterruptEnable(void);
/* -----------------------------------------------------------*/

#endif  /* _DRIVERAPI_H_ */
