/******************************************************
 @File      : question.c
 @Author    : pcmid
 @Contact   : plzcmid@gmail.com
 @Time      : 18-10-26 下午3:56
 @Desc      : from question.h
*******************************************************/

#include "question.h"
#include <string.h>

dns_question_t *dns_question_from_buf(buffer_t *const buffer, const size_t count)
{
    assert(buffer != NULL);
    assert(buffer->offset == 12);

    dns_question_t *question = (dns_question_t *)malloc(sizeof(dns_question_t) * count);

    for(int i = 0; i < count; ++i)
    {
        question[i].name = buf_next_domain(buffer);

        question[i].qtype = buf_next_u16(buffer);

        question[i].qclass = buf_next_u16(buffer);
    }

    return question;
}
