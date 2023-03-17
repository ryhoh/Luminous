/**
 * @file LEDControl.h
 * @author ryhoh
 * @brief LEDデバイスの制御を行う関数群のヘッダファイル
 * 
 */

#ifndef _LED_CONTROLLERS_H_
#define _LED_CONTROLLERS_H_

/* インクルード -----------------------------------------------*/
#include "Common.h"

/* マクロ定義 -------------------------------------------------*/
#define m_LEDCONTROL_DATA_PIN  (2)  ///< データピン番号
#define m_LEDCONTROL_CS_PIN  (3)  ///< チップセレクトピン番号
#define m_LEDCONTROL_CLK_PIN  (4)  ///< クロックピン番号

#define m_LEDCONTROL_MAX7219_SCANLIMIT  (0x0b)  ///< レジスタアドレス: スキャンレベル
#define m_LEDCONTROL_MAX7219_DECODEMODE  (0x09)  ///< レジスタアドレス: デコードモード
#define m_LEDCONTROL_MAX7219_BRIGHTNESS  (0x0a)  ///< レジスタアドレス: 輝度
#define m_LEDCONTROL_MAX7219_DRIVEMODE  (0x0c)  ///< レジスタアドレス: 駆動モード

#define m_LEDCONTROL_MAX7219_SCANLIMIT_8  (0x07)  ///< スキャンレベル8桁
#define m_LEDCONTROL_MAX7219_DECODEMODE_NODECODE  (0x00)  ///< デコードモード: デコードしない
#define m_LEDCONTROL_MAX7219_BRIGHTNESS_MAX  (0x09)  ///< 最大輝度
#define m_LEDCONTROL_MAX7219_BRIGHTNESS_MIN  (0x00)  ///< 最小輝度
#define m_LEDCONTROL_MAX7219_DRIVEMODE_OPERATE  (0x01)  ///< 駆動モード: オペレート

#define m_LEDCONTROL_MAX7219_SETUP_STEP0 (0)  ///< 初期化ステップ0
#define m_LEDCONTROL_MAX7219_SETUP_STEP1 (1)  ///< 初期化ステップ1
#define m_LEDCONTROL_MAX7219_SETUP_STEP5 (5)  ///< 初期化ステップ5
#define m_LEDCONTROL_MAX7219_SETUP_STEP0_DATA_NUM (6)  ///< 初期化ステップ1データ数
#define m_LEDCONTROL_MAX7219_SETUP_STEP1_DATA_NUM (16)  ///< 初期化ステップ2データ数

#define m_LEDCONTROL_MAX7219_PANEL1 (0x01)  ///< パネル1
#define m_LEDCONTROL_MAX7219_PANEL2 (0x02)  ///< パネル2
#define m_LEDCONTROL_MAX7219_PANEL3 (0x03)  ///< パネル3
#define m_LEDCONTROL_MAX7219_PANEL4 (0x04)  ///< パネル4
#define m_LEDCONTROL_MAX7219_PANEL5 (0x05)  ///< パネル5
#define m_LEDCONTROL_MAX7219_PANEL6 (0x06)  ///< パネル6
#define m_LEDCONTROL_MAX7219_PANEL7 (0x07)  ///< パネル7
#define m_LEDCONTROL_MAX7219_PANEL8 (0x08)  ///< パネル8

#define m_LEDCONTROL_MAX7219_BLANK_DATA (0x0F)  ///< 空白データ

/* 構造体定義 -------------------------------------------------*/

/**
 * @brief Controller for Max7219
 * 
 * @note
 *  同期式SPI通信で、MAX7219にデータを送信する
 *  マトリクスLEDが複数接続（MAX7219のカスケード接続）されている場合、
 *  MAX7219に2Byteのデータを送る度に、古いデータが後ろのMAX7219へ押し出される
 *
 *  表示内容の更新を行うには、全体の表示内容を作った上で、
 *  それを1行(1digit)ずつMAX7219の数だけ繰り返して送信し、
 *  8行(8digit)分それを繰り返す
 *
 *  データ送信は (レジスタアドレス 1Byte, データ 1Byte) で行う
 *  レジスタアドレスは 0x01 ~ 0x08 を使う（0スタートでない）ことに注意
 */
typedef struct _Max7219 {
  uint8_t u8_dat;  ///< Pin number connecting dat
  uint8_t u8_lat;  ///< Pin number connecting lat (or cs)
  uint8_t u8_clk;  ///< Pin number connecting clk
  uint8_t u8_brightness;  ///< Brightness of LED (0 ~ 9)
  uint32_t u32_setupStep;  ///< Step of setup
  uint8_t u8_isready;  ///< Flag of setup completion
  uint8_t u8_dummy[7];  ///< Dummy
  uint32_t u32_bufferSize;  ///< Size of buffer 
  uint8_t *pu8_buffer;  ///< Buffer for data to send
} Max7219_t;

/**
 * @brief Initialize Max7219.
 * @param max7219 [in] Pointer of Max7219 to initialize.
*/
void f_LED_MAX7219_init(Max7219 *max7219);

/* 内部関数宣言 -----------------------------------------------*/

// /**
//  * @brief Do test run.
//  * @param max7219 [in] Pointer of Max7219 to test.
// */
// void testRunMax7219(Max7219 *max7219);

/**
 * @brief Flush data from single MatrixLED to Max7219.
 * @param max7219 [in] Pointer of Max7219 to write.
 * @param matrixLED [in] Pointer of MatrixLED to read.
*/
void flushMatrixLEDByMax7219(Max7219 *max7219, MatrixLED *matrixLED);

/**
 * @brief Flush data from multiple MatrixLEDs to Max7219.
 * @param max7219 [in] Pointer of Max7219 to write.
 * @param matrixLEDs [in] Pointer of MatrixLED-Array to read.
 * @param length [in] Length of MatrixLED-Array.
 * @note When length is 1, same to flushMatrixLEDByMax7219.
*/
void flushMatrixLEDsByMax7219(Max7219 *max7219, MatrixLED *matrixLEDs, uint8_t length);

// params: レジスタアドレス, データ
// ラッチ操作を行わないバージョン
static inline void shiftOutToMax7219(Max7219 *max7219, uint8_t addr, uint8_t data)
{
  call_shiftOut(max7219->dat, max7219->clk, MSBFIRST, addr);
  call_shiftOut(max7219->dat, max7219->clk, MSBFIRST, data);
}

// params: レジスタアドレス, データ
// ラッチ操作を行う（1件だけ送る）バージョン
static inline void sendToMax7219(Max7219 *max7219, uint8_t addr, uint8_t data)
{
  call_digitalWrite(max7219->lat, LOW);
  shiftOutToMax7219(max7219, addr, data);
  call_digitalWrite(max7219->lat, HIGH);
  call_digitalWrite(max7219->lat, LOW);
}

#endif  /* _LED_CONTROLLERS_H_ */
