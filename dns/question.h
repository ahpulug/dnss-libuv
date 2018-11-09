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


struct question_s
{
    char *name;
    uint16_t qtype;
    uint16_t qclass;
};

typedef struct question_s questions_t;

struct dns_question_s
{
    size_t count;
    questions_t *questions;
};

typedef struct dns_question_s dns_question_t;

int dns_question_from_buf(dns_question_t *question, buffer_t *buffer, size_t count);

buffer_t *dns_question_to_buf(const dns_question_t *dns_question);

void dns_question_free(dns_question_t *question);

#endif // _QUESTION_H_
