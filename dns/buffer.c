/******************************************************
 @File      : buffer.c
 @Author    : pcmid
 @Contact   : plzcmid@gmail.com
 @Time      : 18-10-27 下午3:02
 @Desc      : from common.h
*******************************************************/

#include <string.h>
#include <arpa/inet.h>
#include "buffer.h"

buffer_t *buf_new(size_t size)
{
    buffer_t *buffer = malloc(sizeof(buffer_t));
    buffer->raw = malloc(size);
    buffer->pos = buffer->raw;
    buffer->len = size;
    return buffer;
}

buffer_t *buf_default()
{
    return buf_new(BUF_DEFAULT_LENGTH);
}

ssize_t buf_cpy(buffer_t *buffer, const char *raw, size_t len)
{
    memcpy(buffer->raw, raw, len);
}


uint8_t read_u8_from_offset(buffer_t *buffer, ssize_t offset)
{
    return (uint8_t)(*(buffer->raw + offset));
}

uint16_t read_u16_from_offset(buffer_t *buffer, ssize_t offset)
{
    return ntohs(
            (((uint16_t)((uint8_t)*(buffer->raw + offset + 0))) << 0) |
            (((uint16_t)((uint8_t)*(buffer->raw + offset + 1))) << 8)
    );
}

uint32_t read_u32_from_offset(buffer_t *buffer, ssize_t offset)
{
    return ntohl(
            (((uint32_t)((uint8_t)*(buffer->raw + offset + 0))) << 0) |
            (((uint32_t)((uint8_t)*(buffer->raw + offset + 1))) << 8) |
            (((uint32_t)((uint8_t)*(buffer->raw + offset + 2))) << 16) |
            (((uint32_t)((uint8_t)*(buffer->raw + offset + 3))) << 24)
    );
}

size_t buf_read_next(buffer_t *buffer, uint8_t *res, size_t len)
{
    memcpy(res, buffer->pos, len);
    buf_pos_skip(buffer, len);
    return len;
}

uint8_t buf_read_next_u8(buffer_t *buffer)
{
    uint8_t res = read_u8_from_offset(buffer, buffer->pos - buffer->raw);
    buffer->pos++;
    return res;
}

uint16_t buf_read_next_u16(buffer_t *buffer)
{
    uint16_t res = read_u16_from_offset(buffer, buffer->pos - buffer->raw);
    buffer->pos += 2;

    return res;
}

uint32_t buf_read_next_u32(buffer_t *buffer)
{
    uint32_t res = read_u32_from_offset(buffer, buffer->pos - buffer->raw);
    buffer->pos += 4;
    return res;
}

void buf_pos_skip(buffer_t *buffer, size_t count)
{
    buffer->pos += count;
}

size_t dns_check_mdns(buffer_t *buffer, size_t offset)
{
    uint16_t dbl_byte = read_u16_from_offset(buffer, offset);

    if((dbl_byte & 0xc000) == 0xc000)
    {
        return (size_t)(dbl_byte & 0x3fff);
    }
    else
    {
        return 0;
    }
}

char *__read_mDNS_domain(buffer_t *const buffer, ssize_t offset)
{
    char domain_tmp[MAX_DOMAIN_LENGTH];
    size_t domain_tmp_len = 0;
    while(*(buffer->raw + offset) != '\0')
    {
        uint8_t len = read_u8_from_offset(buffer, offset);
        memcpy(domain_tmp + domain_tmp_len, buffer->raw + offset, len + 1);
        domain_tmp_len += (len + 1);
        offset += (len + 1);
    }

    char *domain = malloc(domain_tmp_len + 1);
    memcpy(domain, domain_tmp, domain_tmp_len + 1);
    domain[domain_tmp_len] = '\0';
    return domain;
}

size_t read_section_domain(char *domain_pos, buffer_t *buffer, size_t offset)
{
    size_t len = read_u8_from_offset(buffer, offset);
    memcpy(domain_pos, buffer->raw + offset, (size_t)(len + 1));
    return len;
}

char *__read_domain(buffer_t *const buffer, size_t offset)
{
    char domain_tmp[MAX_DOMAIN_LENGTH];
    size_t domain_tmp_len = 0;
    while(*(buffer->raw + offset) != '\0')
    {
        size_t m_offset = 0;
        if((m_offset = dns_check_mdns(buffer, offset)) == 0)
        {
            size_t len = read_section_domain(domain_tmp + domain_tmp_len, buffer, offset);
            domain_tmp_len += (len + 1);
            offset += (len + 1);
        }
        else
        {
            char *res = __read_domain(buffer, m_offset);
            memcpy(domain_tmp + domain_tmp_len, res, strlen(res));
            domain_tmp_len += strlen(res);
            free(res);
            res = NULL;
            offset += 1;
            break;
        }
    }

    offset += 1;
    buffer->pos = buffer->raw + offset;

    char *domain = malloc(domain_tmp_len + 1);

    memcpy(domain, domain_tmp, domain_tmp_len + 1);

    domain[domain_tmp_len] = '\0';

    return domain;
}

char *buf_read_next_domain(buffer_t *buffer)
{
    return __read_domain(buffer, buffer->pos - buffer->raw);
}

void buf_free(buffer_t *buffer)
{
    if(buffer == NULL)
    {
        return;
    }
    free(buffer->raw);
    free(buffer);
    buffer = NULL;
}

size_t buf_write_next(buffer_t *buffer, uint8_t *src, size_t len)
{
    memcpy(buffer->pos, src, len);
    buffer->pos += len;
    return len;
}

int buf_write_next_u8(buffer_t *buffer, uint8_t src)
{
    *(buffer->pos) = src;
    buffer->pos++;
    return 0;
}

int buf_write_next_u16(buffer_t *buffer, uint16_t src)
{
    uint16_t net_u16 = htons(src);
    memcpy(buffer->pos, &net_u16, 2);
    buffer->pos += 2;
    return 0;
}

int buf_write_next_u32(buffer_t *buffer, uint32_t src)
{
    uint32_t net_u32 = htonl(src);
    memcpy(buffer->pos, &net_u32, 4);
    buffer->pos += 4;
    return 0;
}
