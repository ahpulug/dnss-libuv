/******************************************************
 @File      : record.c
 @Author    : pcmid
 @Contact   : plzcmid@gmail.com
 @Time      : 18-10-26 下午3:30
 @Desc      : from record.h
*******************************************************/
#include <string.h>
#include "record.h"


dns_record_t *dns_record_from_buf(buffer_t *const buffer, const size_t count)
{
    dns_record_t *record = (dns_record_t *)malloc(sizeof(dns_record_t) * count);

    for(int i = 0; i < count; ++i)
    {
        char *domain = buf_next_domain(buffer);

        record[i].domain = domain;

        record[i].qtype = buf_next_u16(buffer);
        record[i].qclass = buf_next_u16(buffer);
        record[i].ttl = buf_next_u32(buffer);
        record[i].data_len = buf_next_u16(buffer);

        switch(record[i].qtype)
        {
            case QTYPE_A:
                for(int p = 0; p < 4; ++p)
                {
                    record[i].A.addr[p] = buf_next_u8(buffer);
                }
                break;
            case QTYPE_NS:
                record[i].NS.host = buf_next_domain(buffer);
                break;
            case QTYPE_CNAME:
                record[i].CNAME.host = buf_next_domain(buffer);
                break;
            case QTYPE_MX:
                record[i].MX.priority = buf_next_u16(buffer);
                record[i].MX.host = buf_next_domain(buffer);
            case QTYPE_AAAA:
                for(int p = 0; p < 16; ++p)
                {
                    record[i].AAAA.addr[p] = buf_next_u8(buffer);
                }
                break;
            default:
                record[i].UNKNOW.data = (char *)buf_next(buffer, record[i].data_len);
                break;
        }
    }
    return record;
}