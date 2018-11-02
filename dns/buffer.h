/******************************************************
 @File      : buffer.h
 @Author    : pcmid
 @Contact   : plzcmid@gmail.com
 @Time      : 18-10-26 下午5:19
 @Desc      : 
*******************************************************/

#ifndef _BUFFER_H_
#define _BUFFER_H_

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_BUFFER_LENGTH (8192)
#define MAX_DOMAIN_LENGTH (256)
#define MAX_SECTION_LENGTH (64)

#define     QTYPE_A         1
#define     QTYPE_NS        2
#define     QTYPE_CNAME     5
#define     QTYPE_MX        15
#define     QTYPE_AAAA      28
#define     QTYPE_UNKOWN    255

typedef struct
{
    char *pos;
    size_t offset;
    char buffer[MAX_BUFFER_LENGTH];
}buffer_t;

buffer_t *buf_default(void);

uint8_t *buf_next(buffer_t *buffer, size_t len);

uint8_t buf_next_u8(buffer_t *buffer);

uint16_t buf_next_u16(buffer_t *buffer);

uint32_t buf_next_u32(buffer_t *buffer);

void buf_pos_skip(buffer_t *buffer, size_t count);

char *buf_next_domain(buffer_t *buffer);

void buf_free(buffer_t *buffer);

#endif // _BUFFER_H_
