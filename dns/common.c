/******************************************************
 @File      : common.c
 @Author    : pcmid
 @Contact   : plzcmid@gmail.com
 @Time      : 18-10-27 下午3:02
 @Desc      : from common.h
*******************************************************/

#include "common.h"

uint16_t read_u16(buffer_t *pos)
{
    return (((uint16_t)*pos) << 8) | ((uint16_t)*(pos + 1));
}