/**
 * @file Middle_pub.h
 * @author ryhoh
 * @brief Middle層の公開ヘッダファイル
 * 
 */

#ifndef _MIDDLE_PUB_H_
#define _MIDDLE_PUB_H_

/* インクルード -----------------------------------------------*/
#include "Middle\LEDControl.h""

/* 外部公開用関数 ---------------------------------------------*/
extern MatrixBuffer_t *f_LED_Get_MatrixBuffer(void);


#endif  /* _MIDDLE_PUB_H_ */