/******************************************************
 @File      : record.h
 @Author    : pcmid
 @Contact   : plzcmid@gmail.com
 @Time      : 18-10-26 下午3:30
 @Desc      : 
*******************************************************/

#ifndef _RECORD_H_
#define _RECORD_H_

#include <stdint.h>
#include "buffer.h"
#include "message.h"

struct dns_record_s
{
    size_t count;
    dns_msg_t *msgs;
};
typedef struct dns_record_s dns_record_t;

int dns_record_from_buf(dns_record_t *record, buffer_t *buffer, size_t count);

void dns_record_free(dns_record_t *record);

#endif // _RECORD_H_
