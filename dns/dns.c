/******************************************************
 @File      : dns.c
 @Author    : pcmid
 @Contact   : plzcmid@gmail.com
 @Time      : 18-10-24 下午8:03
 @Desc      : from dns.h
*******************************************************/

#include "dns.h"

int dns_from_buf(dns_t *dns, char *buf)
{
    assert(dns != NULL);
    buffer_t *buffer = buf_default(buf);

    dns_header_from_buf(&dns->header, buffer);
    dns_question_from_buf(&dns->question, buffer, dns->header.question_rrs);
    dns_record_from_buf(&dns->record, buffer, dns->header.record_rrs);
    dns_additional_from_buf(&dns->additional, buffer, dns->header.additional_rss);
    dns_authority_from_buf(&dns->authority, buffer, dns->header.autority_rss);

    buf_free(buffer);
    return 0;
}

buffer_t *dns_to_buf(const dns_t *dns)
{
    return 0;
}

void dns_free(dns_t *dns)
{
}
