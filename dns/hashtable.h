/******************************************************
 @File      : hashtable.h
 @Author    : pcmid
 @Contact   : plzcmid@gmail.com
 @Time      : 18-11-5 下午12:37
 @Desc      : 
*******************************************************/

#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#define MAX_TABLE_LENGTH (16)

typedef struct node_s
{
    void *value;
    char *key;
    unsigned int hash;
    struct node_s *next;
}node_t;

typedef struct hashtable_s
{
    unsigned int count;
    node_t *table[MAX_TABLE_LENGTH];
}hashtable_t;

hashtable_t *hashtable_default();

int ht_put(hashtable_t *hashtable, char *key, void *value);

void *ht_get(hashtable_t *hashtable, char *key);

int ht_remove(hashtable_t *hashtable, char *key);

#endif // _HASHTABLE_H_
