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
    Queue *p= (Queue *)malloc(sizeof(Queue));
    p->size = 0;
    p->head = NULL;
    p->tail = NULL;
    *queue = p;
}

node_t* get_queue(Queue *queue)
{
    if (queue->size == 0) {
        return NULL;
    }
    return queue->head->value;
}

node_t* pop_queue(Queue *queue)
{
    if (queue->size == 0) {
        return NULL;
    }
    node_t *value = queue->head->value;
    queue_node_t *p = queue->head;
    queue->head = p->next;
    free(p);
    queue->size--;
    return value;
}

void insert_queue(Queue *queue, node_t *value)
{
    queue_node_t *p = (queue_node_t *)malloc(sizeof(queue_node_t));
    p->value = value;
    p->next = NULL;
    queue->tail->next = p;
    queue->tail = p;
    queue->size++;
}

int size_queue(Queue *queue)
{
    return queue->size;
}

void print_queue(Queue *queue)
{
    queue_node_t *p;
    p = queue->head;
    while (p != NULL) {
        printf("%d ", p->value->value);
        p = p->next;
    }
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
    printf("start create queue");
    create_queue(&queue);
    printf("queue create done, size=%d\n", queue->size);
    insert_queue(queue, tree);
    while (size_queue(queue) > 0) {
        node_t *t = pop_queue(queue);
        printf("%d ", t->value);
        if (t->left) {
            insert_queue(queue, t->left);
        }
        if (t->right) {
            insert_queue(queue, t->right);
        }
    }
    printf("%d ", tree->value);
    print_tree(tree->left);
    print_tree(tree->right);
}

int main()  
{  
	node_t *tree;
    printf("####\n");
	create_tree(&tree, 0);
	print_tree(tree);

    return 0;  
}  
