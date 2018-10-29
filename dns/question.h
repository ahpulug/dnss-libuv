/******************************************************
 @File      : question.h
 @Author    : pcmid
 @Contact   : plzcmid@gmail.com
 @Time      : 18-10-26 下午3:56
 @Desc      : 
*******************************************************/

#ifndef _QUESTION_H_
#define _QUESTION_H_


#include "buffer.h"


struct dns_question_s
{
    char *name;
    uint16_t qtype;
    uint16_t qclass;
};

typedef struct dns_question_s dns_question_t;

dns_question_t *dns_question_from_buf(buffer_t *const buffer, const size_t count);

buffer_t *dns_question_to_buf(const dns_question_t *dns_question);

#endif // _QUESTION_H_
