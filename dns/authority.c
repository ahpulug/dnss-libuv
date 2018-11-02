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

    authority->msgs = malloc(sizeof(authority->msgs) * count);

    for(int i = 0; i < count; ++i)
    {
        authority->msgs[i] = dns_msg_from_buf(buffer);
    }

    return authority;
}

void dns_authority_free(dns_authority_t *authority)
{
    if(authority == NULL)
    {
        return;
    }

    for(int i = 0; i < authority->count; ++i)
    {
        dns_msg_free(authority->msgs[i]);
    }
    free(authority->msgs);
    free(authority);
}
