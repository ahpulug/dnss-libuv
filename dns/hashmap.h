/******************************************************
 @File      : hashmap.h
 @Author    : pcmid
 @Contact   : plzcmid@gmail.com
 @Time      : 18-11-5 下午12:37
 @Desc      : 
*******************************************************/

#ifndef _MULTIMAP_H_
#define _MULTIMAP_H_

#include <stdlib.h>

#define MAX_MAP_LENGTH (32)

typedef struct node_s
{
    void *value;
    char *key;
    unsigned int hash;
    struct node_s *next;
}node_t;

typedef struct hashmap_s
{
    unsigned int count;
    node_t *table[MAX_MAP_LENGTH];
}hashmap_t;

hashmap_t *map_default();

int map_put(hashmap_t *map, char *key, void *value);

void *map_get(hashmap_t *map, char *key);

void *map_remove(hashmap_t *map, char *key);

#endif // _MULTIMAP_H_
