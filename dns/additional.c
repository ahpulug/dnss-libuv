/******************************************************
 @File      : additional.c
 @Author    : pcmid
 @Contact   : plzcmid@gmail.com
 @Time      : 18-10-26 下午5:25
 @Desc      : from additional.h
*******************************************************/

#include "additional.h"

int dns_additional_from_buf(dns_additional_t *additional, buffer_t *buffer, size_t count)
{
    additional->count = count;

    additional->msgs = malloc(sizeof(dns_msg_t) * count);

    for(int i = 0; i < count; ++i)
    {
        dns_msg_from_buf(&additional->msgs[i], buffer);
    }

    return 0;
}
