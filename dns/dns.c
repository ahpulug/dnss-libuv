/******************************************************
 @File      : dns.c
 @Author    : pcmid
 @Contact   : plzcmid@gmail.com
 @Time      : 18-10-24 下午8:03
 @Desc      : from dns.h
*******************************************************/

#include "dns.h"

dns_t *dns_from_buf(buffer_t *const buffer)
{
    dns_t *dns = (dns_t *)malloc(sizeof(dns_t));

    dns->header = dns_header_from_buf(buffer);

    dns->question = dns_question_from_buf(buffer, dns->header->question_rrs);

    dns->record = dns_record_from_buf(buffer, dns->header->record_rrs);

    dns->authority = dns_authority_from_buf(buffer, dns->header->autority_rss);

    dns->additional = dns_additional_from_buf(buffer, dns->header->additional_rss);

    return 0;
}

buffer_t *dns_to_buf(const dns_t *dns)
{
    return 0;
}

int dns_free(dns_t *dns)
{
    dns_header_free(dns->header);
    dns_question_free(dns->question);

}