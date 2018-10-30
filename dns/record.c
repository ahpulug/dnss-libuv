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
        char *domain = read_domain(buffer);

        record[i].qtype = buf_next_u16(buffer);

        switch(record[i].qtype)
        {
            case QTYPE_A:
                record[i].A.domain = domain;
                record[i].A.qclass = buf_next_u16(buffer);
                record[i].A.ttl = buf_next_u32(buffer);

                //skip data length
                buf_pos_skip(buffer, 2);

                for(int p = 0; p < 4; ++p)
                {
                    record[i].A.addr[p] = buf_next_u8(buffer);
                }
                break;

            case QTYPE_NS:
                break;
            case QTYPE_CNAME:
                record[i].CNAME.domain = domain;
                record[i].CNAME.qclass = buf_next_u16(buffer);
                record[i].CNAME.ttl = buf_next_u32(buffer);
                record[i].CNAME.data_len = buf_next_u16(buffer);
                record[i].CNAME.host = read_domain(buffer);
                break;
                //beacons.gcp.gvt2.com
        }
    }
    return NULL;
}