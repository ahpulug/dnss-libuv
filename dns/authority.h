/******************************************************
 @File      : authority.h
 @Author    : pcmid
 @Contact   : plzcmid@gmail.com
 @Time      : 18-10-26 下午5:24
 @Desc      : 
*******************************************************/

#ifndef _AUTHORITY_H_
#define _AUTHORITY_H_

#include "buffer.h"

struct dns_authority_s
{
    /*
     * 18-10-27
     * TODO: parse it in the feature
     */
    uint16_t _len;
    char * buf;
};

typedef struct dns_authority_s dns_authority_t;

#endif // _AUTHORITY_H_
