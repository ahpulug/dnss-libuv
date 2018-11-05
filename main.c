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

    cache_t *cache = init_cache();

    for(int i = 0; i < 10; i++)
    {
        buffer_t *buffer = buf_default();

        len = chilen;
        n = recvfrom(sockfd, buffer->buffer, MAX_BUFFER_LENGTH, 0, pcliaddr, &len);
        assert(n >= 0);


        dns_t *dns = dns_from_buf(buffer);

        if(dns == NULL)
        {
            continue;
        }
        if(dns->header->response == 0)
        {
            entry_t *entry = cache_get(cache, dns->question->questions[0].name);
            if(entry)
            {
                printf("cache hit : %s", entry->dns->question->questions[0].name);
            }
        }
        else
        {
            cache_put(cache, dns);
        }

        buf_free(buffer);

        sendto(sockfd, "response\n\0", 10, 0, pcliaddr, len);
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