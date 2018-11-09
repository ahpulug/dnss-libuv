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

    char *domain = buf_next_domain(buffer);

    message->domain = domain;

    message->qtype = buf_next_u16(buffer);
    message->qclass = buf_next_u16(buffer);
    message->ttl = buf_next_u32(buffer);
    message->data_len = buf_next_u16(buffer);

    message->data = malloc(sizeof(int8_t) * message->data_len);

    message->data = buf_next(buffer, message->data_len);

    return 0;
}

void dns_msg_free(dns_msg_t *message)
{
    if(message == NULL)
    {
        return;
    }

    if(message->domain != NULL)
    {
        free(message->domain);
    }

    if(message->data != NULL)
    {
        free(message->data);
    }
    free(message);
}

dns_msg_t *dns_msg_clone(dns_msg_t *message)
{
    dns_msg_t *msg_cloned = malloc(sizeof(dns_msg_t));

    char *domain = malloc(strlen(message->domain) + 1);

    uint8_t *data = malloc(message->data_len);

    memcpy(msg_cloned, message, sizeof(dns_msg_t));

    msg_cloned->domain = domain;
    msg_cloned->data = data;

    return msg_cloned;
}
