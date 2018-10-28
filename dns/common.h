/******************************************************
 @File      : common.h
 @Author    : pcmid
 @Contact   : plzcmid@gmail.com
 @Time      : 18-10-26 下午5:19
 @Desc      : 
*******************************************************/

#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <assert.h>

#define MAX_DOMAIN_LENGTH 256

typedef char buffer_t;

uint16_t read_u16(buffer_t *pos);

#endif // _COMMON_H_
