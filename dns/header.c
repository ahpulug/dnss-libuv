/******************************************************
 @File      : header.c
 @Author    : pcmid
 @Contact   : plzcmid@gmail.com
 @Time      : 18-10-26 下午3:55
 @Desc      : from header.h
*******************************************************/

#include "header.h"
#include <string.h>
#include <stdio.h>

int parse_flag(dns_header_t *header, flag_t flag)
{
    assert(header != NULL);

    //response 1 bit,mask 0x8000
    header->flag.response = (uint8_t)((*(uint8_t *)&flag & (uint16_t)0x8000) >> 15);

    //operation_code 4bit,mask 0x7800
    header->flag.operation_code = (uint8_t)((*(uint8_t *)&flag & (uint16_t)0x7800) >> 11);

    //authoritative_answer 1bit,mask 0x400
    header->flag.authoritative_answer = (uint8_t)((*(uint8_t *)&flag & (uint16_t)0x400) >> 10);

    //truncated_message 1bit,mask 0x200
    header->flag.truncated_message = (uint8_t)((*(uint8_t *)&flag & (uint16_t)0x200) >> 9);

    //recursion_desired 1bit,mask 0x100
    header->flag.recursion_desired = (uint8_t)((*(uint8_t *)&flag & (uint16_t)0x100) >> 8);

    //recursion_avilable 1bit,mask 0x80
    header->flag.recursion_avilable = (uint8_t)((*(uint8_t *)&flag & (uint16_t)0x80) >> 7);

    //z 1bit,mask 0x40
    header->flag.z = (uint8_t)((*(uint8_t *)&flag & (uint16_t)0x40) >> 6);

    //authed_data 1bit,mask 0x20
    header->flag.authed_data = (uint8_t)((*(uint8_t *)&flag & (uint16_t)0x20) >> 5);

    //checking_disabled 1bit,mask 0x10
    header->flag.checking_disabled = (uint8_t)((*(uint8_t *)&flag & (uint16_t)0x10) >> 4);

    //response_code 4bit,mask 0xf
    header->flag.response_code = (uint8_t)((*(uint8_t *)&flag & (uint16_t)0xf) >> 0);

    return 0;
}

int dns_header_from_buf(dns_header_t *header, buffer_t *buffer)
{
    assert(header != NULL);

    //parse id
    header->id = buf_read_next_u16(buffer);

    flag_t flag;
    buf_read_next(buffer, (uint8_t *)&header->flag, 2);

    header->question_rrs = buf_read_next_u16(buffer);

    header->record_rrs = buf_read_next_u16(buffer);

    header->autority_rss = buf_read_next_u16(buffer);

    header->additional_rss = buf_read_next_u16(buffer);

    return 0;
}

void dns_header_to_buf(buffer_t *buffer, const dns_header_t *header)
{
    buf_write_next_u16(buffer, header->id);
    buf_write_next(buffer, (uint8_t *)&header->flag, 2);
    buf_write_next_u16(buffer, header->question_rrs);
    buf_write_next_u16(buffer, header->record_rrs);
    buf_write_next_u16(buffer, header->autority_rss);
    buf_write_next_u16(buffer, header->additional_rss);
}
