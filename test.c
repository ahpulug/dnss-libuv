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

    char buf[BUF_DEFAULT_LENGTH];

    fread(buf, size, 1, fp);

    cache_t *cache = cache_default();


    int i = 1;
    while(i--)
    {
        dns_t *dns = dns_default();
        dns_from_buf(dns, buf, BUF_DEFAULT_LENGTH);

        dns_t *dns_new = dns_default();
        buffer_t *buf_new = buf_default();

        dns_to_buf(dns, buf_new);

        dns_from_buf(dns_new, buf_new->raw, BUF_DEFAULT_LENGTH);

        buf_free(buf_new);
        dns_free(dns_new);


        cache_put(cache, dns);
        dns_t *dns1 = dns_default();
        dns_from_buf(dns1, buf, BUF_DEFAULT_LENGTH);
        cache_put(cache, dns1);
    }
    cache_free(cache);

}