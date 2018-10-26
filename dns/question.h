/******************************************************
 @File      : question.h
 @Author    : pcmid
 @Contact   : plzcmid@gmail.com
 @Time      : 18-10-26 下午3:56
 @Desc      : 
*******************************************************/

#ifndef _QUESTION_H_
#define _QUESTION_H_

#include "common.h"

enum query_type_e
{
    A = 1,
    NS = 2,
    CNAME = 5,
    MC = 15,
    AAAA = 28,
    UNKOWN = 255,
};

struct dns_question_s
{
    char *name;
    uint16_t qtype;
};

typedef struct dns_question_s dns_question_t;

#endif // _QUESTION_H_
