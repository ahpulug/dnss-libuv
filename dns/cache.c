/******************************************************
 @File      : cache.c
 @Author    : pcmid
 @Contact   : plzcmid@gmail.com
 @Time      : 18-11-5 下午12:19
 @Desc      : from cache.h
*******************************************************/

#include <time.h>
#include "cache.h"

entry_t *init_entry(time_t rawtime, dns_t *dns)
{
    entry_t *entry = malloc(sizeof(entry_t));

    entry->time = rawtime;
    entry->dns = dns;
    return entry;
}

void free_entry(entry_t *entry)
{
    dns_free(entry->dns);
    free(entry);
}

cache_t *init_cache()
{
    return map_default();
}

dns_t *cache_get(cache_t *cache, char *domain)
{
    entry_t *entry = map_get(cache, domain);


    time_t nowtime;
    time(&nowtime);

    if(entry != NULL)
    {
        if(entry->dns->record.count > 0 && nowtime >= (entry->dns->record.msgs[0].ttl + entry->time))
        {
            return entry->dns;
        }
        else
        {
            cache_remove(cache, domain);
        }
    }

    return NULL;
}

int cache_put(cache_t *cache, dns_t *dns)
{

    time_t rawtime;
    time(&rawtime);

    entry_t *entry = init_entry(rawtime, dns);

    return map_put(cache, dns->question.questions[0].name, entry);
}

int cache_remove(cache_t *cache, char *domain)
{
    entry_t *entry = map_get(cache, domain);
    if(entry == NULL)
    {
        return -1;
    }
    free_entry(entry);

    map_remove(cache, domain);
    return 0;
}
