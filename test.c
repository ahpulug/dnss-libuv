/******************************************************
 @File      : test.c
 @Author    : pcmid
 @Contact   : plzcmid@gmail.com
 @Time      : 18-11-10 下午6:28
 @Desc      : from test.h
*******************************************************/

#include <stdio.h>
#include <sys/stat.h>
#include "dns/cache.h"

int main(int argc, char **argv)
{
    struct stat statbuf;
    stat(argv[1], &statbuf);
    ssize_t size = statbuf.st_size;

    FILE *fp = fopen(argv[1], "r");

    char buf[MAX_BUFFER_LENGTH];

    fread(buf, size, 1, fp);

    cache_t *cache = cache_default();


    int i = 10;
    while(i--)
    {
        dns_t *dns = malloc(sizeof(dns_t));
        dns_from_buf(dns, buf);
        cache_put(cache, dns);
        dns_t *dns1 = malloc(sizeof(dns_t));
        dns_from_buf(dns1, buf);
        cache_put(cache, dns1);
        cache_remove(cache, dns1->question.questions[0].name);
//        dns_free(dns);
    }

}