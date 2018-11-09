/******************************************************
 @File      : additional.h
 @Author    : pcmid
 @Contact   : plzcmid@gmail.com
 @Time      : 18-10-26 下午5:25
 @Desc      : 
*******************************************************/

#ifndef _ADDITIONAL_H_
#define _ADDITIONAL_H_

#include "buffer.h"
#include "message.h"

struct dns_additional_s
{
    size_t count;
    dns_msg_t *msgs;
};

typedef struct dns_additional_s dns_additional_t;

int dns_additional_from_buf(dns_additional_t *additional, buffer_t *buffer, size_t count);

void dns_additional_free(dns_additional_t *additional);

#endif // _ADDITIONAL_H_
