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
#include "message.h"

struct dns_authority_s
{
    size_t count;
    dns_msg_t *msg;
};

typedef struct dns_authority_s dns_authority_t;

dns_authority_t *dns_authority_from_buf(buffer_t *const buffer, const size_t count);

#endif // _AUTHORITY_H_
