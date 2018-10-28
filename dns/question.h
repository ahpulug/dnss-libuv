/******************************************************
 @File      : question.h
 @Author    : pcmid
 @Contact   : plzcmid@gmail.com
 @Time      : 18-10-26 下午3:56
 @Desc      : 
*******************************************************/

#ifndef _QUESTION_H_
#define _QUESTION_H_

#define MAX_DOMAIN_LENGTH 256

#include "common.h"


#define     QTYPE_A         1
#define     QTYPE_NS        2
#define     QTYPE_CNAME     5
#define     QTYPE_MX        15
#define     QTYPE_AAAA      28
#define     QTYPE_UNKOWN    255


struct dns_question_s
{
    char *name;
    uint16_t qtype;
};

typedef struct dns_question_s dns_question_t;

dns_question_t *dns_question_from_buf(const buffer_t *buffer, size_t *pos);

buffer_t *dns_question_to_buf(const dns_question_t *dns_question);

#endif // _QUESTION_H_
