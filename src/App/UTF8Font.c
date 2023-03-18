/**
 * @file UTF8Font.c
 * @author ryhoh
 * @brief UTF-8フォントデータ用関数
 * 
 */

/* インクルード -----------------------------------------------*/
#include "App\UTF8Font.h"

/* 関数定義 ---------------------------------------------------*/
/**
 * @brief 指定したUTF-8文字のフォントデータを取得する
 * 
 * @param i8_c 取得する文字
 * @param u8_matrix フォントデータ格納先
 * @retval uint8_t フォントデータ
 * @retval uint8_t N/Aデータ
 */
void f_FONT_UTF8_ReadChar(uint32_t u32_code, uint8_t u8_matrix[])
{
    static uint32_t su32_code_cache = m_FONT_UTF_INVALID_CODE;
    static uint32_t su32_index_cache = 0;
    uint32_t u32_index;
    
    /* キャッシュがあればそれを使う */
    if ((su32_index_cache != m_FONT_UTF_INVALID_CODE) && (su32_code_cache == u32_code)) {
        u32_index = su32_index_cache;
    } else {
        uint32_t u32_index = f_FONT_UTF8_binarySearchForCode(u32_code);
        su32_index_cache = u32_index;
    }

    if (u32_index == m_FONT_UTF_INVALID_CODE) {
        for (uint8_t u8_i = 0; u8_i < m_FONT_UTF_HEIGHT; u8_i++) {
            u8_matrix[u8_i] = f_driver_readByteFromROM(gscu8_FONT_UTF_NA_CHAR + u8_i);
        }
        return;
    }
    
    for (uint8_t u8_i = 0; u8_i < m_FONT_UTF_HEIGHT; u8_i++) {
        u8_matrix[u8_i] = f_driver_readByteFromROM(gscu8_FONT_UTF_FONTS + u32_index * m_FONT_UTF_WIDTH + u8_i);
    }
}

/**
 * @brief 指定したUTF-8文字のフォントデータを取得する
 * 
 * @param u32_code 取得する文字コード
 * @retval uint8_t 文字コードのインデックス
 * @retval uint8_t ない場合は m_FONT_UTF_INVALID_CODE を返す
 * 
 */
static const uint32_t *f_FONT_UTF8_binarySearchForCode(uint32_t u32_code) {
    uint32_t u32_imin = 0;
    uint32_t u32_imax = m_FONT_UTF_CODES_LEN - 1;
    while (u32_imin <= u32_imax) {
        // linear search for small area
        if (u32_imax - u32_imin < m_FONT_UTF_LINEAR_SEARCH_SIZE) {
            for (uint16_t entry_i = u32_imin; entry_i < u32_imax + 1; ++entry_i) {
                if (f_driver_readWordFromROM(gscu32_FONT_UTF8_CODES + entry_i) == u32_code) {
                    return entry_i;
                }
            }
            // not found
            return m_FONT_UTF_INVALID_CODE;
        }

        {
            const uint32_t u32_imid = u32_imin + (u32_imax - u32_imin) / 2;
            const uint32_t looking_code = f_driver_readWordFromROM(gscu32_FONT_UTF8_CODES + u32_imid);

            if (looking_code > u32_code)
                u32_imax = u32_imid - 1;
            else if (looking_code < u32_code)
                u32_imin = u32_imid + 1;
            else
                return u32_imid;
        }
    }
    return m_FONT_UTF_INVALID_CODE;
}

