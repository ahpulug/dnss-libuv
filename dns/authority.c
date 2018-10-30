/******************************************************
 @File      : authority.c
 @Author    : pcmid
 @Contact   : plzcmid@gmail.com
 @Time      : 18-10-26 下午5:24
 @Desc      : from authority.h
*******************************************************/

#include "authority.h"

dns_authority_t *dns_authority_from_buf(buffer_t *const buffer, const size_t count)
{
    dns_authority_t *authority = malloc(sizeof(dns_authority_t));

    authority->count = count;

    authority->msg = malloc(sizeof(authority->msg) * count);

    for(int i = 0; i < count; ++i)
    {
        authority->msg[i] = dns_msg_from_buffer(buffer);
    }

    return authority;
}