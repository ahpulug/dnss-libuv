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
    dns_msg_t *msg;
};

typedef struct dns_additional_s dns_additional_t;

dns_additional_t *dns_additional_from_buf(buffer_t *const buffer, const size_t count);

#endif // _ADDITIONAL_H_
