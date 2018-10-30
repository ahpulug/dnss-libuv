/******************************************************
 @File      : record.c
 @Author    : pcmid
 @Contact   : plzcmid@gmail.com
 @Time      : 18-10-26 下午3:30
 @Desc      : from record.h
*******************************************************/
#include <string.h>
#include "record.h"


dns_record_t *dns_record_from_buf(buffer_t *const buffer, const size_t count)
{
    dns_record_t *record = (dns_record_t *)malloc(sizeof(dns_record_t));

    record->count = count;

    record->msgs = malloc(sizeof(record->msgs) * count);

    for(int i = 0; i < count; ++i)
    {
        record->msgs[i] = dns_msg_from_buffer(buffer);
    }
    return record;
}