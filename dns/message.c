/******************************************************
 @File      : message.c
 @Author    : pcmid
 @Contact   : plzcmid@gmail.com
 @Time      : 18-10-30 下午9:04
 @Desc      : from message.h
*******************************************************/

#include <string.h>
#include "message.h"

int dns_msg_from_buf(dns_msg_t *message, buffer_t *buffer)
{

    char *domain = buf_read_next_domain(buffer);

    message->domain = domain;

    message->qtype = buf_read_next_u16(buffer);
    message->qclass = buf_read_next_u16(buffer);
    message->ttl = buf_read_next_u32(buffer);
    message->data_len = buf_read_next_u16(buffer);

    message->data = malloc(sizeof(int8_t) * message->data_len);

    buf_read_next(buffer, message->data, message->data_len);

    return 0;
}

int dns_msg_to_buf(buffer_t *buffer, const dns_msg_t *message)
{
    buf_write_next(buffer, (uint8_t *)message->domain, strlen(message->domain) + 1);
    buf_write_next_u16(buffer, message->qtype);
    buf_write_next_u16(buffer, message->qclass);
    buf_write_next_u32(buffer, message->ttl);
    buf_write_next_u16(buffer, message->data_len);
    buf_write_next(buffer, message->data, message->data_len);
    return 0;
}

void dns_msg_inner_free(dns_msg_t *message)
{
    if(message == NULL)
    {
        return;
    }

    if(message->domain != NULL)
    {
        free(message->domain);
        message->domain = NULL;
    }

    if(message->data != NULL)
    {
        free(message->data);
        message->data = NULL;
    }
}

