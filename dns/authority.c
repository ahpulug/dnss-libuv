/******************************************************
 @File      : authority.c
 @Author    : pcmid
 @Contact   : plzcmid@gmail.com
 @Time      : 18-10-26 下午5:24
 @Desc      : from authority.h
*******************************************************/

#include "authority.h"

int dns_authority_from_buf(dns_authority_t *authority, buffer_t *buffer, size_t count)
{
    authority->count = count;

    authority->msgs = malloc(sizeof(dns_msg_t) * count);

    for(int i = 0; i < count; ++i)
    {
        dns_msg_from_buf(&authority->msgs[i], buffer);
    }

    return 0;
}

int dns_authority_to_buf(buffer_t *buffer, const dns_authority_t *authority)
{
    for(int i = 0; i < authority->count; ++i)
    {
        dns_msg_to_buf(buffer, &authority->msgs[i]);
    }
    return 0;
}

