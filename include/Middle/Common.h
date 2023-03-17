/**
 * @file Common.h
 * @author ryhoh
 * @brief ミドルウェア層向け共通ヘッダ
 * 
 */

#ifndef _MIDDLE_COMMON_H_
#define _MIDDLE_COMMON_H_

/* インクルード -----------------------------------------------*/
#include <stdint.h>

/* マクロ定義 -------------------------------------------------*/
#define UINT8_MAX (255U)
#define UINT16_MAX (65535U)
#define UINT32_MAX (4294967295UL)
#define m_OUTPUT (1)
#define m_INPUT  (0)
#define m_HIGH (1)
#define m_LOW  (0)
#define m_TRUE (1)
#define m_FALSE (0)
#define m_ON (1)
#define m_OFF (0)

#define M_CLIPINC(x, max) do ((x) < (max) ? (x) + 1 : (max)) while(0)

#endif  /* _MIDDLE_COMMON_H_ */
