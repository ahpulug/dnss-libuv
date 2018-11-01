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

    dns_question_t *question = (dns_question_t *)malloc(sizeof(dns_question_t));

    question->count = count;
    question->questions = malloc(sizeof(questions_t) * count);

    for(int i = 0; i < count; ++i)
    {
        question->questions[i].name = buf_next_domain(buffer);

        question->questions[i].qtype = buf_next_u16(buffer);

        question->questions[i].qclass = buf_next_u16(buffer);
    }

    return question;
}

void dns_question_free(dns_question_t *question)
{
    if(question == NULL)
    {
        return;
    }

    if(question->count != 0)
    {
        for(int i = 0; i < question->count; ++i)
        {
            free(question->questions[i].name);
        }
        free(question->questions);
    }
    free(question);
}
