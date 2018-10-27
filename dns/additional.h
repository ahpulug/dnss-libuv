/******************************************************
 @File      : additional.h
 @Author    : pcmid
 @Contact   : plzcmid@gmail.com
 @Time      : 18-10-26 下午5:25
 @Desc      : 
*******************************************************/

#ifndef _ADDITIONAL_H_
#define _ADDITIONAL_H_

#include "common.h"

struct dns_additional_s
{
    /*
     * 18-10-27
     * TODO: parse it in the feature
     */
    uint16_t _len;
    char *buf;
};

typedef struct dns_additional_s dns_additional_t;

#endif // _ADDITIONAL_H_
