#include <stdio.h>  
#include <stdlib.h>  
  
typedef struct node_t {
	struct node_t *left;
	struct node_t *right;
	int value;
} node_t;

#define N 7
int tree_values[] = {1,2,3,4,-1,5,6};

  
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
    printf("%d ", tree->value);
    print_tree(tree->left);
    print_tree(tree->right);
}

int main()  
{  
	node_t *tree;

	create_tree(&tree, 0);
	print_tree(tree);

	return 0;  
}  
