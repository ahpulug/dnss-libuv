/******************************************************
 @File      : additional.c
 @Author    : pcmid
 @Contact   : plzcmid@gmail.com
 @Time      : 18-10-26 下午5:25
 @Desc      : from additional.h
*******************************************************/

#include "additional.h"

dns_additional_t *dns_additional_from_buf(buffer_t *const buffer, const size_t count)
{
    dns_additional_t *additional = malloc(sizeof(dns_additional_t));

    additional->count = count;

    additional->msgs = malloc(sizeof(additional->msgs) * count);

    for(int i = 0; i < count; ++i)
    {
        additional->msgs[i] = dns_msg_from_buf(buffer);
    }

    return additional;
}

void dns_additional_free(dns_additional_t *additional)
{
    if(additional == NULL)
    {
        return;
    }

    for(int i = 0; i < additional->count; ++i)
    {
        dns_msg_free(additional->msgs[i]);
    }
    free(additional->msgs);
    free(additional);
}
