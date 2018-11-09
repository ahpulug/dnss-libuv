/******************************************************
 @File      : hashmap.c
 @Author    : pcmid
 @Contact   : plzcmid@gmail.com
 @Time      : 18-11-5 下午12:37
 @Desc      : from hashmap.h
*******************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hashmap.h"

node_t *init_node(char *str, void *value);

void free_node(node_t *node);

unsigned int bkdr_hash(char *const str)
{
    unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;

    char *pos = str;

    while(*pos)
    {
        hash = hash * seed + (*pos++);
    }

    return (hash & 0x7FFFFFFF);
}

hashmap_t *map_default()
{
    hashmap_t *map = malloc(sizeof(hashmap_t));
    map->count = 0;

    for(int i = 0; i < MAX_MAP_LENGTH; ++i)
    {
        map->table[i] = NULL;
    }

    return map;
}

void *map_get(hashmap_t *map, char *key)
{
    unsigned int hash = bkdr_hash(key);
    unsigned int index = hash % MAX_MAP_LENGTH;
    for(node_t *n = map->table[index]; n; n = n->next)
    {
        if((n->hash == hash) && (strcmp(n->key, key) == 0))
        {
            return n->value;
        }
    }

    return NULL;
}

int map_put(hashmap_t *map, char *key, void *value)
{
    node_t *node = init_node(key, value);

    unsigned int index = node->hash % MAX_MAP_LENGTH;


    for(node_t *n = map->table[index]; n; n = n->next)
    {
        if((n->hash == node->hash) && (strcmp(n->key, key) == 0))
        {
            //replace
            n->value = value;
            return 0;
        }
    }

    //insert into the head
    node->next = map->table[index];
    map->table[index] = node;
    return 0;
}


void *map_remove(hashmap_t *map, char *key)
{
    unsigned int hash = bkdr_hash(key);

    unsigned int index = hash % MAX_MAP_LENGTH;

    node_t *prev = map->table[index];
    node_t *n = prev;

    while(n)
    {
        node_t *next = n->next;
        if((n->hash == hash) && (strcmp(n->key, key) == 0))
        {
            prev->next = next;
            free_node(n);
            return 0;
        }
        prev = n;
        n = next;
    }
    return NULL;
}

node_t *init_node(char *str, void *value)
{
    node_t *node = malloc(sizeof(node_t));
    node->key = malloc(strlen(str) + 1);
    memcpy(node->key, str, strlen(str) + 1);
    node->value = value;

    node->hash = bkdr_hash(str);
    node->next = NULL;

    return node;
}

void free_node(node_t *node)
{
    if(node == NULL)
    {
        return;
    }

    free(node->key);
    free(node);
}

