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
    dns_msg_t *msgs;
};

typedef struct dns_authority_s dns_authority_t;

int dns_authority_from_buf(dns_authority_t *authority, buffer_t *buffer, size_t count);

int dns_authority_to_buf(buffer_t *buffer, const dns_authority_t *authority);

#endif // _AUTHORITY_H_
