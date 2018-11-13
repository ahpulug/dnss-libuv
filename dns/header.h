/******************************************************
 @File      : header.h
 @Author    : pcmid
 @Contact   : plzcmid@gmail.com
 @Time      : 18-10-26 下午3:55
 @Desc      : 
*******************************************************/

#ifndef _HEADER_H_
#define _HEADER_H_

#include <stdint.h>
#include <asm/byteorder.h>
#include "buffer.h"

typedef struct
{
#if defined(__LITTLE_ENDIAN_BITFIELD)
    uint8_t recursion_desired:1,
            truncated_message:1,
            authoritative_answer:1,
            operation_code:4,
            response:1;

    uint8_t response_code:4,
            checking_disabled:1,
            authed_data:1,
            z:1,
            recursion_avilable:1;


#elif defined(__BIG_ENDIAN_BITFIELD)
    uint8_t response:1,
            operation_code:4,
            authoritative_answer:1,
            truncated_message:1,
            recursion_desired:1;

    uint8_t recursion_avilable:1,
            z:1,
            authed_data:1,
            checking_disabled:1,
            response_code:4;


#else
#error    "Please fix <asm/byteorder.h>"
#endif

}flag_t;

struct dns_header_s
{
    uint16_t id;

    flag_t flag;

    uint16_t question_rrs;
    uint16_t record_rrs;
    uint16_t autority_rss;
    uint16_t additional_rss;
};

typedef struct dns_header_s dns_header_t;

int dns_header_from_buf(dns_header_t *header, buffer_t *buffer);

void dns_header_to_buf(buffer_t *buffer, const dns_header_t *header);

#endif // _HEADER_H_
