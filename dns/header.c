/******************************************************
 @File      : header.c
 @Author    : pcmid
 @Contact   : plzcmid@gmail.com
 @Time      : 18-10-26 下午3:55
 @Desc      : from header.h
*******************************************************/

#include "header.h"

int parse_flag(dns_header_t *header, uint16_t flag)
{
    assert(header != NULL);

    //response 1 bit,mask 0x8000
    header->response = (flag & (uint16_t)0x8000) >> 15;

    //operation_code 4bit,mask 0x7800
    header->operation_code = (flag & (uint16_t)0x7800) >> 11;

    //authoritative_answer 1bit,mask 0x400
    header->authoritative_answer = (flag & (uint16_t)0x400) >> 10;

    //truncated_message 1bit,mask 0x200
    header->truncated_message = (flag & (uint16_t)0x200) >> 9;

    //recursion_desired 1bit,mask 0x100
    header->recursion_desired = (flag & (uint16_t)0x100) >> 8;

    //recursion_avilable 1bit,mask 0x80
    header->recursion_avilable = (flag & (uint16_t)0x80) >> 7;

    //z 1bit,mask 0x40
    header->z = (flag & (uint16_t)0x40) >> 6;

    //authed_data 1bit,mask 0x20
    header->authed_data = (flag & (uint16_t)0x20) >> 5;

    //checking_disabled 1bit,mask 0x10
    header->checking_disabled = (flag & (uint16_t)0x10) >> 4;

    //response_code 4bit,mask 0xf
    header->response_code = (flag & (uint16_t)0xf) >> 0;

    return 0;

}

dns_header_t *dns_header_from_buf(const buffer_t *buffer, size_t pos)
{
    dns_header_t *header = (dns_header_t *)malloc(sizeof(dns_header_t));

    //parse id
    header->id = read_u16((buffer_t *)(buffer + pos));
    pos += 2;

    uint16_t flag = 0;
    flag = read_u16((buffer_t *)(buffer + pos));
    parse_flag(header, flag);
    pos += 2;

    header->questions = read_u16((buffer_t *)(buffer + pos));
    pos += 2;

    header->answers = read_u16((buffer_t *)(buffer + pos));
    pos += 2;

    header->autority_rss = read_u16((buffer_t *)(buffer + pos));
    pos += 2;

    header->additional_rss = read_u16((buffer_t *)(buffer + pos));
    pos += 2;

    return header;
}

buffer_t *dns_header_to_buf(const dns_header_t *header)
{
    return 0;
}

