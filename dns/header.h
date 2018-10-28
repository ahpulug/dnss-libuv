/******************************************************
 @File      : header.h
 @Author    : pcmid
 @Contact   : plzcmid@gmail.com
 @Time      : 18-10-26 下午3:55
 @Desc      : 
*******************************************************/

#ifndef _HEADER_H_
#define _HEADER_H_

#include "common.h"

struct dns_header_s
{
    uint16_t id;

    uint16_t response:1;
    uint16_t operation_code:4;
    uint16_t authoritative_answer:1;
    uint16_t truncated_message:1;
    uint16_t recursion_desired:1;
    uint16_t recursion_avilable:1;
    uint16_t z:1;
    uint16_t authed_data:1;
    uint16_t checking_disabled:1;
    uint16_t response_code:4;

    uint16_t questions;
    uint16_t answers;
    uint16_t autority_rss;
    uint16_t additional_rss;
};

typedef struct dns_header_s dns_header_t;

dns_header_t *dns_header_from_buf(const buffer_t *buffer, size_t * buf_pos);

buffer_t *dns_header_to_buf(const dns_header_t *header);

#endif // _HEADER_H_
