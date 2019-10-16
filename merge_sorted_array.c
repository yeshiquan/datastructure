/*
 * 合并两个有序数组，方法：在数组末尾插入一个虚拟元素MAX_INT
 */
#include <stdio.h>
#include <string.h>

#define MAX_INT ~(1<<31)

#define M 4 
#define N 2 

int A[M] = {1,2,6};
int B[N] = {2,5};
int C[M+N];

void print_array(int *a, int s, int t) 
{
    for (int i = 0; i <= t; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main()
{
	int	i = 0; 
    int j = 0;
    int k = 0;
    int pe;

    while (k < (M+N)) {
        pe = j < N ? B[j]: MAX_INT;
        for (; i < M && A[i] <= pe; i++) {
            C[k++] = A[i];
        }
        pe = i < M ? A[i]: MAX_INT;
        for (; j < N && B[j] <= pe; j++) {
            C[k++] = B[j];
        }
    }

    print_array(C, 0, M+N-1);

	return 0;
}
