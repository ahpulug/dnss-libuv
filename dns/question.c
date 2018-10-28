/******************************************************
 @File      : question.c
 @Author    : pcmid
 @Contact   : plzcmid@gmail.com
 @Time      : 18-10-26 下午3:56
 @Desc      : from question.h
*******************************************************/

#include "question.h"
#include <string.h>

dns_question_t *dns_question_from_buf(const buffer_t *buffer, size_t *pos)
{
    assert((*pos) == 12);

    //parse qname

    dns_question_t *question = (dns_question_t *)malloc(sizeof(dns_question_t));

    char *tmp = (char *)malloc(MAX_DOMAIN_LENGTH);
    size_t tmp_pos;
    for(tmp_pos = 0; tmp_pos < MAX_DOMAIN_LENGTH; tmp_pos++, (*pos)++)
    {
        tmp[tmp_pos] = *(buffer + (*pos));
        if(*(buffer + (*pos)) == '\0')
        {
            break;
        }
    }

    char *const qname = (char *)malloc(tmp_pos + 1);

    memcpy(qname, tmp, tmp_pos + 1);

    free(tmp);
    tmp = 0;

    question->name = qname;

    // parse qtype
    (*pos)++;

    question->qtype = read_u16((buffer_t *)(buffer + *pos));

    return question;
}
