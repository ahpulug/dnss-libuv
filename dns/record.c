/******************************************************
 @File      : record.c
 @Author    : pcmid
 @Contact   : plzcmid@gmail.com
 @Time      : 18-10-26 下午3:30
 @Desc      : from record.h
*******************************************************/
#include <string.h>
#include "record.h"


int dns_record_from_buf(dns_record_t *record, buffer_t *const buffer, const size_t count)
{
    record->count = count;

    record->msgs = malloc(sizeof(dns_msg_t) * count);

    for(int i = 0; i < count; ++i)
    {
        dns_msg_from_buf(&record->msgs[i], buffer);
    }
    return 0;
}
