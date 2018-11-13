/******************************************************
 @File      : message.h
 @Author    : pcmid
 @Contact   : plzcmid@gmail.com
 @Time      : 18-10-30 下午9:04
 @Desc      : 
*******************************************************/

#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <stdint.h>
#include "buffer.h"

struct dns_msg_A_s
{
    uint8_t addr[4];
};

struct dns_msg_NS_s
{
    char *host;
};

struct dns_msg_CNAME_s
{
    char *host;
};

struct dns_msg_MX_s
{
    uint16_t priority;
    char *host;
};

struct dns_msg_AAAA_s
{
    uint8_t addr[16];
};

struct dns_msg_UNKNOW_s
{
    char *data;
};

typedef struct dns_msg_A_s dns_msg_A_t;
typedef struct dns_msg_NS_s dns_msg_NS_t;
typedef struct dns_msg_CNAME_s dns_msg_CNAME_t;
typedef struct dns_msg_MX_s dns_msg_MX_t;
typedef struct dns_msg_AAAA_s dns_msg_AAAA_t;
typedef struct dns_msg_UNKNOW_s dns_msg_UNKNOW_t;

struct dns_msg_s
{
    char *domain;
    uint16_t qtype;
    uint16_t qclass;
    uint32_t ttl;
    uint16_t data_len;
    uint8_t *data;
};

typedef struct dns_msg_s dns_msg_t;

int dns_msg_from_buf(dns_msg_t *message, buffer_t *buffer);

void dns_msg_inner_free(dns_msg_t *message);

int dns_msg_to_buf(buffer_t *buffer, const dns_msg_t * message);

#endif // _MESSAGE_H_
