/******************************************************
 @File      : record.h
 @Author    : pcmid
 @Contact   : plzcmid@gmail.com
 @Time      : 18-10-26 下午3:30
 @Desc      : 
*******************************************************/

#ifndef _RECORD_H_
#define _RECORD_H_

#include <stdint.h>
#include "buffer.h"

struct dns_rc_A_s
{
    char *domain;
    uint16_t qclass;
    uint32_t ttl;
    uint8_t addr[4];
};

struct dns_rc_NS_s
{
    char *domain;
    char *host;
    uint32_t ttl;
};

struct dns_rc_CNAME_s
{
    char *domain;
    uint16_t qclass;
    uint32_t ttl;
    uint16_t data_len;
    char *host;
};

struct dns_rc_MX_s
{
    char *domain;
    uint16_t priority;
    char *host;
    uint32_t ttl;
};

struct dns_rc_AAAA_s
{
    char *domain;
    uint8_t addr[16];
    uint32_t ttl;
};

struct dns_rc_UNKNOW_s
{
    char *domain;
    uint32_t ttl;
    uint16_t date_len;
};

typedef struct dns_rc_A_s dns_rc_A_t;
typedef struct dns_rc_NS_s dns_rc_NS_t;
typedef struct dns_rc_CNAME_s dns_rc_CNAME_t;
typedef struct dns_rc_MX_s dns_rc_MX_t;
typedef struct dns_rc_AAAA_s dns_rc_AAAA_t;
typedef struct dns_rc_UNKNOW_s dns_rc_UNKNOW_t;

struct dns_record_s
{
    uint16_t qtype;
    union
    {
        dns_rc_A_t A;
        dns_rc_NS_t NS;
        dns_rc_CNAME_t CNAME;
        dns_rc_MX_t MX;
        dns_rc_AAAA_t AAAA;
        dns_rc_UNKNOW_t UNKNOW;
    };
};
typedef struct dns_record_s dns_record_t;

dns_record_t *dns_record_from_buf(buffer_t *const buffer, const size_t count);

#endif // _RECORD_H_
