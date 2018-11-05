/******************************************************
 @File      : cache.h
 @Author    : pcmid
 @Contact   : plzcmid@gmail.com
 @Time      : 18-11-5 下午12:19
 @Desc      : 
*******************************************************/

#ifndef _CACHE_H_
#define _CACHE_H_

#include <stdint.h>
#include "hashtable.h"
#include "dns.h"

struct entry_s
{
    time_t time;
    dns_t *dns;
};

typedef struct entry_s entry_t;
typedef hashtable_t cache_t;

cache_t *init_cache();

entry_t *cache_get(cache_t *cache, char *domain);

int cache_put(cache_t *cache, dns_t *dns);

int cache_remove(cache_t *cache, char *domain);


#endif // _CACHE_H_
