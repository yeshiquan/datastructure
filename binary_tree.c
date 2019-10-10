#include <stdio.h>  
#include <stdlib.h>  

typedef struct node_t {
    struct node_t *left;
    struct node_t *right;
    int value;
} node_t;

typedef struct queue_node_t {
    struct queue_node_t *next;
    node_t *value;
    int v;
} queue_node_t;

typedef struct Queue {
    queue_node_t *head;
    queue_node_t *tail;
    int size;
} Queue;

#define N 7
int tree_values[] = {1,2,3,4,-1,5,6};

void create_queue(Queue **queue)
{
    queue_node_t *node= (queue_node_t *)malloc(sizeof(queue_node_t));
    node->next = NULL;
    node->value = 0;

    Queue *p= (Queue *)malloc(sizeof(Queue));
    p->size = 0;
    p->head = node;
    p->tail = node;
    *queue = p;
}

node_t* get_queue(Queue *queue)
{
    if (queue->size == 0) {
        return NULL;
    }
    return queue->head->next->value;
}

void print_queue(Queue *queue)
{
    queue_node_t *p;
    p = queue->head->next;
    printf("queue: [");
    while (p != NULL) {
        printf("%d,", p->value->value);
        p = p->next;
    }
    printf("]\n");
}

node_t* pop_queue(Queue *queue)
{
    queue_node_t *p = queue->head->next;
    if (p == NULL) {
        return NULL;
    }
    node_t *value = p->value;
    queue->head->next = p->next;
    if (p->next == NULL) {
        queue->tail = queue->head;
    }
    free(p);
    queue->size--;
    //printf("pop queue done, size = %d\n", queue->size);
    print_queue(queue);
    return value;
}

void push_queue(Queue *queue, node_t *value)
{
    queue_node_t *p = (queue_node_t *)malloc(sizeof(queue_node_t));
    p->value = value;
    p->next = NULL;
    queue->tail->next = p;
    queue->tail = p;
    queue->size++;
    //printf("push queue done, size=%d\n", queue->size);
    print_queue(queue);
}

int size_queue(Queue *queue)
{
    return queue->size;
}

void create_tree(node_t **tree, int i)
{
    node_t *p;

    if (i >= N) {
        return;
    }

    printf("create node i = %d\n", i);

    if (tree_values[i] == -1) {
        return;
    }

    p = (node_t *)malloc(sizeof(node_t));
    p->value = tree_values[i];
    p->left = NULL;
    p->right = NULL;
    create_tree(&p->left, 2*i+1);
    create_tree(&p->right, 2*i+2);
    *tree = p;
}

void print_tree(node_t *tree) {
    if (tree == NULL) return;

    Queue *queue;
    create_queue(&queue);

    push_queue(queue, tree);
    while (1) {
        node_t *t = pop_queue(queue);
        if (t == NULL) break;
        printf("tree node: %d\n", t->value);
        if (t->left) {
            push_queue(queue, t->left);
        }
        if (t->right) {
            push_queue(queue, t->right);
        }
    }
}

int main()  
{  
    node_t *tree;
    create_tree(&tree, 0);
    print_tree(tree);

    return 0;  
}  
