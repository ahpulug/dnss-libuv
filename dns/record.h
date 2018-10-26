/******************************************************
 @File      : record.h
 @Author    : pcmid
 @Contact   : plzcmid@gmail.com
 @Time      : 18-10-26 下午3:30
 @Desc      : 
*******************************************************/

#ifndef _RECORD_H_
#define _RECORD_H_

#include "common.h"

struct dns_rc_A_s
{
    char *domain;
    /*
     * 18-10-26
     * TODO: change to ipv4 addr type
     */
    char *addr;
    uint32_t ttl;
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
    char *host;
    uint32_t ttl;
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
    /*
     * 18-10-26
     * TODO: change to ipv6 addr type
     */
    char *addr;
    uint32_t ttl;
};

struct dns_rc_UNKNOW_s
{
    char *domain;
    uint16_t qtype;
    uint32_t ttl;
    uint16_t date_len;
};

typedef struct dns_rc_A_s dns_rc_A_t;
typedef struct dns_rc_NS_s dns_rc_NS_t;
typedef struct dns_rc_CNAME_s dns_rc_CNAME_t;
typedef struct dns_rc_MX_s dns_rc_MX_t;
typedef struct dns_rc_AAAA_s dns_rc_AAAA_t;
typedef struct dns_rc_UNKNOW_s dns_rc_UNKNOW_t;

union dns_record
{
    dns_rc_A_t A;
    dns_rc_NS_t NS;
    dns_rc_CNAME_t CNAME;
    dns_rc_MX_t MX;
    dns_rc_AAAA_t AAAA;
    dns_rc_UNKNOW_t UNKNOW;
};

typedef union dns_record dns_record_t;

#endif // _RECORD_H_
