/******************************************************
 @File      : buffer.c
 @Author    : pcmid
 @Contact   : plzcmid@gmail.com
 @Time      : 18-10-27 下午3:02
 @Desc      : from common.h
*******************************************************/

#include <string.h>
#include "buffer.h"

buffer_t *new_buffer(void)
{
    buffer_t *buffer = malloc(sizeof(buffer_t));
    buffer->pos = buffer->buffer;
    buffer->offset = 0;
    return buffer;
}

uint8_t read_u8_from_offset(buffer_t *buffer, ssize_t offset)
{
    return (uint8_t)(*(buffer->buffer + offset));
}

uint16_t read_u16_from_offset(buffer_t *buffer, ssize_t offset)
{
    return (uint16_t)(
            ((((uint16_t)(*(buffer->buffer + offset + 0))) << 8) & 0xff00) |
            ((((uint16_t)(*(buffer->buffer + offset + 1))) << 0) & 0x00ff)
    );
}

uint32_t read_u32_from_offset(buffer_t *buffer, ssize_t offset)
{
    return (uint32_t)(
            ((((uint32_t)(*(buffer->buffer + offset + 0))) << 24) & 0xff000000) |
            ((((uint32_t)(*(buffer->buffer + offset + 1))) << 16) & 0x00ff0000) |
            ((((uint32_t)(*(buffer->buffer + offset + 2))) << 8) & 0x0000ff00) |
            ((((uint32_t)(*(buffer->buffer + offset + 3))) << 0) & 0xff0000ff)
    );
}

uint8_t *buf_next(buffer_t *buffer, size_t len)
{
    uint8_t *const res = malloc(sizeof(uint8_t) * len);
    memcpy(res, buffer->pos, len);
    buf_pos_skip(buffer, len);
    return res;
}

uint8_t buf_next_u8(buffer_t *buffer)
{
    uint8_t res = read_u8_from_offset(buffer, buffer->offset);
    buffer->pos++;
    buffer->offset++;
    return res;
}

uint16_t buf_next_u16(buffer_t *buffer)
{
    uint16_t res = read_u16_from_offset(buffer, buffer->offset);
    buffer->pos += 2;
    buffer->offset += 2;

    return res;
}

uint32_t buf_next_u32(buffer_t *buffer)
{
    uint32_t res = read_u32_from_offset(buffer, buffer->offset);
    buffer->pos += 4;
    buffer->offset += 4;
    return res;
}

void buf_pos_skip(buffer_t *buffer, size_t count)
{
    buffer->pos += count;
    buffer->offset += count;
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
    while(*(buffer->buffer + offset) != '\0')
    {
        uint8_t len = read_u8_from_offset(buffer, offset);
        memcpy(domain_tmp + domain_tmp_len, buffer->buffer + offset, len + 1);
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
    memcpy(domain_pos, buffer->buffer + offset, (size_t)(len + 1));
    return len;
}

char *__read_domain(buffer_t *const buffer, size_t offset)
{
    char domain_tmp[MAX_DOMAIN_LENGTH];
    size_t domain_tmp_len = 0;
    while(*(buffer->buffer + offset) != '\0')
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
            offset += 1;
            break;
        }
    }

    offset += 1;
    buffer->offset = offset;
    buffer->pos = buffer->buffer + offset;

    char *domain = malloc(domain_tmp_len + 1);

    memcpy(domain, domain_tmp, domain_tmp_len + 1);

    domain[domain_tmp_len] = '\0';

    return domain;
}


char *buf_next_domain(buffer_t *buffer)
{
    return __read_domain(buffer, buffer->offset);
}
