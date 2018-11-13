/******************************************************
 @File      : question.c
 @Author    : pcmid
 @Contact   : plzcmid@gmail.com
 @Time      : 18-10-26 下午3:56
 @Desc      : from question.h
*******************************************************/

#include "question.h"
#include <string.h>

int dns_question_from_buf(dns_question_t *question, buffer_t *const buffer, const size_t count)
{
    question->count = count;
    question->questions = malloc(sizeof(questions_t) * count);

    for(int i = 0; i < count; ++i)
    {
        question->questions[i].name = buf_read_next_domain(buffer);

        question->questions[i].qtype = buf_read_next_u16(buffer);

        question->questions[i].qclass = buf_read_next_u16(buffer);
    }

    return 0;
}

int dns_question_to_buf(buffer_t *buffer,const dns_question_t *question)
{
    for(int i = 0; i < question->count; ++i)
    {
        buf_write_next(buffer, (uint8_t *)question->questions[i].name, strlen(question->questions[i].name) + 1);
        buf_write_next_u16(buffer, question->questions[i].qtype);
        buf_write_next_u16(buffer, question->questions[i].qclass);
    }
    return 0;
}
