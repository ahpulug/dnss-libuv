/******************************************************
 @File      : hashtable.c
 @Author    : pcmid
 @Contact   : plzcmid@gmail.com
 @Time      : 18-11-5 下午12:37
 @Desc      : from hashtable.h
*******************************************************/

#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

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

hashtable_t *hashtable_default()
{
    hashtable_t *hashtable = malloc(sizeof(hashtable_t));
    hashtable->count = 0;

    return hashtable;
}

int ht_put(hashtable_t *hashtable, char *key, void *value)
{
    node_t *node = init_node(key, value);
    if(node == NULL || node->value == NULL)
    {
        return -1;
    }

    unsigned int index = node->hash % MAX_TABLE_LENGTH;

    for(node_t *n = hashtable->table[index]; n; n = n->next)
    {
        if((n->hash == node->hash) && (strcmp(n->key, node->key) == 0))
        {
            n->value = node->value;
            return 0;
        }
    }

    node->next = hashtable->table[index];
    hashtable->table[index] = node;

    hashtable->count++;

    return 0;
}

void *ht_get(hashtable_t *hashtable, char *key)
{

    unsigned int hash = bkdr_hash(key);
    unsigned int index = hash % MAX_TABLE_LENGTH;
    for(node_t *n = hashtable->table[index]; n; n = n->next)
    {
        if((n->hash == hash) && (strcmp(n->key, key) == 0))
        {
            return n->value;
        }
    }

    return NULL;
}

int ht_remove(hashtable_t *hashtable, char *key)
{
    unsigned int hash = bkdr_hash(key);

    unsigned int index = hash % MAX_TABLE_LENGTH;

    node_t *prev = hashtable->table[index];
    node_t *n = prev;

    while(n)
    {
        node_t *next = n->next;
        if((n->hash == hash) && (strcmp(n->key, key) == 0))
        {
            prev->next = next;
            free_node(n);
        }
        prev = n;
        n = next;
    }
    return 0;
}

node_t *init_node(char *str, void *value)
{
    node_t *node = malloc(sizeof(node_t));
    node->key = str;
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

    if(node->key)
    {
        free(node->key);
    }

    if(node->value)
    {
        free(node->value);
    }

    free(node);
}

