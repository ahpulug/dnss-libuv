#include <stdio.h>
#include <uv.h>
#include <stdlib.h>
#include <assert.h>
#include <strings.h>

#include "dns/dns.h"

void dg_read(int sockfd, struct sockaddr *pcliaddr, socklen_t chilen)
{
    ssize_t n;
    socklen_t len;

    buffer_t *buffer = buf_default();

    for(int i = 0; i < 10; i++)
    {
        len = chilen;
        n = recvfrom(sockfd, buffer->buffer, MAX_BUFFER_LENGTH, 0, pcliaddr, &len);
        assert(n >= 0);
        dns_t *dns = dns_from_buf(buffer);
        dns_free(dns);
        buf_free(buffer);
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