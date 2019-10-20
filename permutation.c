#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
  
#define DEBUG  
  
#ifdef DEBUG  
#define debug(...) printf( __VA_ARGS__)   
#else  
#define debug(...)  
#endif  

#define N 3

char arr[N] = {'A', 'B', 'C'};

/*
A A交换, A B C
    B B交换
        A B C
    B C交换
        A C B
A B交换, B A C
    A A交换
        B A C
    A C交换
        B C A
A C交换 C B A
    B B交换
        C B A 
    B A交换
        C A B 
*/

void swap(char *a, char *b) 
{
    char tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void print_array(char *a, int s, int t)
{
    int i;
    for (i = s; i <= t; i++) {
        printf("%c ", a[i]);
    }
    printf("\n");
}

void permutation(int k)
{
    if (k == N) {
        print_array(arr, 0, N-1);
        return;
    }
    for (int i = k; i < N; i++) {
        swap(arr+k, arr+i);
        permutation(k+1);
        swap(arr+i, arr+k);
    }
}
  
int main()  
{  
    permutation(0);
}  
