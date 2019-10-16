/*
 * 理解快速排序，先把最后一个元素抽空，然后让i和j总是指向抽空的那个元素
 */
#include <stdio.h>
#include <string.h>

#define N 7 

int A[] = {2,3,46,0,8,11,18};

void print_array(int *a, int s, int t) 
{
    for (int i = 0; i <= t; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int partition(int *a, int l, int r)
{
	int i = l, j = r;
	int x = a[r]; 
	while (i < j) {
		while(i < j && a[i] <= x)
			i++;  
		if(i < j) {
			a[j] = a[i]; 
		}
		while(i < j && a[j] >= x) 
			j--;  
		if(i < j) {
			a[i] = a[j]; 
		}
	}
	a[i] = x;

	return i;
}

/* 选择数组中第i大的元素并返回 */
int quick_select(int *a, int s, int t, int i)
{
	int		p, m;

	if (s == t) return a[t];
	p = partition(a, s, t);	/* 用a[t]分割数组 */
	m = p - s + 1;			/* m是a[t]在小组内的排名 */
	if (m == i) return a[p];
	if (m > i) {
		return quick_select(a, s, p-1, i);
	}
	return quick_select(a, p+1, t, i-m);
}

void quick_sort(int *a, int s, int t)
{
	int 	p;

	if (s < t) {
		p = partition(a, s, t);
		quick_sort(a, s, p-1);
		quick_sort(a, p+1, t);
	}
}


int main()
{
	int	i;
	quick_sort(A, 0, N-1);
	print_array(A, 0, N-1);
	printf("第%d大的数为%d\n", 4, quick_select(A, 0, N-1, 4));

	return 0;
}
