#include <stdio.h>
#include <uv.h>
#include <stdlib.h>
#include <assert.h>
#include <strings.h>

#include "dns/dns.h"
#include "dns/cache.h"

void dg_read(int sockfd, struct sockaddr *pcliaddr, socklen_t chilen)
{
    ssize_t n;
    socklen_t len;

    cache_t *cache = cache_default();

    for(int i = 0; i < 10; i++)
    {
        char buffer[BUF_DEFAULT_LENGTH];

        len = chilen;
        n = recvfrom(sockfd, buffer, BUF_DEFAULT_LENGTH, 0, pcliaddr, &len);

        assert(n >= 0);

        dns_t *dns = malloc(sizeof(dns_t));

        dns_from_buf(dns, buffer, BUF_DEFAULT_LENGTH);

        if(dns->header.flag.response == 0)
        {
            dns_t *dns_cache;
            if((dns_cache = cache_get(cache, dns->question.questions[0].name)) != NULL)
            {
                printf("cache hit\n");
            }
        }
        else
        {
            cache_put(cache, dns);
        }

        sendto(sockfd, "response\n", 9, 0, pcliaddr, len);
    }
}

int main()
{
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    assert(sockfd != 0);

    bzero(&server_addr, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(15353);
    bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    dg_read(sockfd, (struct sockaddr *)&client_addr, sizeof(client_addr));
}
