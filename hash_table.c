/**
 * 哈希表的实现
 * @author yeshiquan@gmail.com
 * @date 2014-03-20
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE  10

//哈希表结构体
typedef struct hash_entry_t {
    struct hash_entry_t *next;
    char *key;
    char *value;
} hash_entry_t;

/**
 * 哈希函数
 * @str 字符串
 * @len 字符串长度
 * @return 返回哈希值
 */
unsigned int hash(char *str, unsigned int len)
{
    unsigned int hash = 5381;
    unsigned int i = 0;

    for (i = 0; i < len; str++, i++) {
        hash = ((hash << 5) + hash) + (*str);
    }

    return hash;
}

/**
 * 插入一个序对
 * @ht 哈希表指针
 * @key 键
 * @value 值
 */
void insert(hash_entry_t *ht, char *key, char *value)
{
    unsigned pos; 
    hash_entry_t * new_entry;

    pos = hash(key, strlen(key)) % MAX_SIZE;
    new_entry = (hash_entry_t *)malloc(sizeof(hash_entry_t));

    new_entry->next = ht[pos].next;
    new_entry->key = key;
    new_entry->value = value;

    ht[pos].next = new_entry;
}

/**
 * 删除序对
 * @ht 哈希表指针
 * @key 键
 * @value 值
 */
char *delete(hash_entry_t *ht, char *key)
{
    unsigned pos = hash(key, strlen(key)) % MAX_SIZE;
    hash_entry_t *p, *q;

    q = ht + pos;
    p = q->next;
    while (p) {
        if (strcmp(key, p->key) == 0) break;
        q = p;
        p = p->next;
    }

    if (p && q) {
        q->next = p->next;
        free(p->key);
        free(p->value);
        free(p);
    }
}

/**
 * 查找值 
 * @ht 哈希表指针
 * @key 键
 * @return 找到返回值，否则返回空
 */
char *find(hash_entry_t *ht, char *key)
{
    unsigned pos = hash(key, strlen(key)) % MAX_SIZE;
    hash_entry_t *p;

    for (p = ht[pos].next; p && strcmp(key, p->key); p = p->next);
    if (p) {
        return p->value;
    }

    return NULL;
}

/**
 * 初始化哈希表
 * @pht 哈希表的指针地址,因为要改变哈希表的指针，所以传入其地址
 */
void make_hash_table(hash_entry_t **pht)
{
    int i;

    *pht = (hash_entry_t *)malloc(sizeof(hash_entry_t) * MAX_SIZE);
    for (i = 0; i < MAX_SIZE; i++) {
        (*pht)[i].next = NULL;
    }
}

/**
 * 遍历哈希表，并打印键值
 * @ht 哈希表指针
 */
void print_hash_table(hash_entry_t *ht)
{
    int i;
    int has_entry;
    hash_entry_t *p;

    for (i = 0; i < MAX_SIZE; i++) {
        p = ht[i].next;
        has_entry = 0;
        while (p) {
            has_entry = 1;
            printf("%s --> %s\n", p->key, p->value);
            p = p->next;
        }
        if (has_entry) {
            printf("\n");
        }
    }
}

int main () 
{
    hash_entry_t *ht;

    make_hash_table(&ht);

    int i;
    char key[50];
    char value[50];
    for (i = 0; i < MAX_SIZE; i++) {
        sprintf(key, "key%d", i);
        sprintf(value, "value%d", i);
        insert(ht, strdup(key), strdup(value));
    }

    printf("%s's value: %s\n", "key4", find(ht, "key4"));
    delete(ht, "key4");
    print_hash_table(ht);

    return 1;
}
