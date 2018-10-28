/******************************************************
 @File      : dns.h
 @Author    : pcmid
 @Contact   : plzcmid@gmail.com
 @Time      : 18-10-24 下午8:03
 @Desc      : 
*******************************************************/

#ifndef _DNS_H_
#define _DNS_H_

#include "header.h"
#include "question.h"
#include "record.h"
#include "authority.h"
#include "additional.h"

struct dns_s
{
    size_t pos;
    dns_header_t *header;
    dns_question_t *questions;
    dns_record_t *record;
    dns_authority_t *authority;
    dns_additional_t *additional;
};

typedef struct dns_s dns_t;

dns_t *dns_from_buf(const buffer_t *buffer);

buffer_t *dns_to_buf(const dns_t *dns);

#endif // _DNS_H_
