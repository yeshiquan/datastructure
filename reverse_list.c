/**
 * 链表逆序的实现
 * @author yeshiquan@gmail.com
 * @date 2014-03-20
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//定义链表节点
typedef struct node_t {
    struct node_t *next;
    char *data;
} node_t;

//插入一个新节点
void insert(node_t *list, char *data)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->data = data;
    node->next = list->next;
    list->next = node;
}

//初始化链表
void make_list(node_t **list)
{
    *list = (node_t *)malloc(sizeof(node_t));
    (*list)->next = NULL;
}

//反转链表
void reverse_list(node_t **list)
{
    node_t *p, *q, *tmp;

    p = NULL;
    q = (*list)->next;
    while (q) {
        tmp = q->next;
        q->next = p;
        p = q;
        q = tmp;
    }
    (*list)->next = p;
}

//打印链表
void print_list(node_t *list)
{
    node_t *p;

    p = list->next;
    while (p) {
        printf("%s->", p->data);
        p = p->next;
    }
    printf("\n");
}

int main () 
{
    node_t *list, *p;

    make_list(&list);

    insert(list, "A");
    insert(list, "B");
    insert(list, "C");
    insert(list, "D");

    print_list(list);

    reverse_list(&list);

    print_list(list);

    return 1;
}
