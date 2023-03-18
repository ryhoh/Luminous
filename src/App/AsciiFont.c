/**
 * @file AsciiFont.c
 * @author ryhoh
 * @brief Ascii font data.
 * 
 */

/* インクルード -----------------------------------------------*/
#include "App\AsciiFont.h"

/* 関数定義 ---------------------------------------------------*/
/**
 * @brief Get a row of indicated ascii char.
 * @param c [in] Char to get font.
 * @param matrix [out] Font matrix. Expected to be 8-length at least.
 * @retval uint8_t matrix data on success.
 * @retval uint8_t N/A data on illegal c.
*/
static inline void f_FONT_ASCII_ReadChar(char i8_c, uint8_t u8_matrix[])
{
    for (uint8_t u8_i = 0; u8_i < m_FONT_ASCII_HEIGHT; u8_i++) {
        if (i8_c - m_FONT_ASCII_ADDRESS_OFFSET < 0 || m_FONT_ASCII_NUM <= i8_c - m_FONT_ASCII_ADDRESS_OFFSET) {
            u8_matrix[u8_i] = *(gscu8_FONT_ASCII_NA_CHAR + u8_i);
        }

        u8_matrix[u8_i] = f_driver_readByteFromROM(*(gscu8_FONT_ASCII_FONTS + i8_c - m_FONT_ASCII_ADDRESS_OFFSET) + u8_i);
    }
}
