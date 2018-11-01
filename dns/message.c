/******************************************************
 @File      : message.c
 @Author    : pcmid
 @Contact   : plzcmid@gmail.com
 @Time      : 18-10-30 下午9:04
 @Desc      : from message.h
*******************************************************/

#include "message.h"

int dns_msg_from_buf(dns_msg_t *message, buffer_t *buffer)
{
    assert(message != NULL);

    char *domain = buf_next_domain(buffer);

    message->domain = domain;

    message->qtype = buf_next_u16(buffer);
    message->qclass = buf_next_u16(buffer);
    message->ttl = buf_next_u32(buffer);
    message->data_len = buf_next_u16(buffer);

    switch(message->qtype)
    {
        case QTYPE_A:
            for(int p = 0; p < 4; ++p)
            {
                message->A.addr[p] = buf_next_u8(buffer);
            }
            break;
        case QTYPE_NS:
            message->NS.host = buf_next_domain(buffer);
            break;
        case QTYPE_CNAME:
            message->CNAME.host = buf_next_domain(buffer);
            break;
        case QTYPE_MX:
            message->MX.priority = buf_next_u16(buffer);
            message->MX.host = buf_next_domain(buffer);
        case QTYPE_AAAA:
            for(int p = 0; p < 16; ++p)
            {
                message->AAAA.addr[p] = buf_next_u8(buffer);
            }
            break;
        default:
            message->UNKNOW.data = (char *)buf_next(buffer, message->data_len);
            break;
    }
    return 0;
}
