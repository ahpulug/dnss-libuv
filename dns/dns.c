/******************************************************
 @File      : dns.c
 @Author    : pcmid
 @Contact   : plzcmid@gmail.com
 @Time      : 18-10-24 下午8:03
 @Desc      : from dns.h
*******************************************************/

#include "dns.h"

dns_t *dns_from_buf(const buffer_t *buffer)
{
    dns_t *dns = (dns_t *)malloc(sizeof(dns_t));

    dns->header = dns_header_from_buf(buffer);

    return 0;
}

buffer_t *dns_to_buf(const dns_t *dns)
{
    return 0;
}