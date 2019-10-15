/*
 * 顺时针打印数组
 */

#include <stdio.h>
#include <stdlib.h>

#define M 3
#define N 3

int A[M][N];

void walk_recursive(int s, int t, int m, int n) 
{
    if (m <=0 || n <= 0) {
        return;
    }

    //起始点的对角坐标
    int es = s+m-1;
    int et = t+n-1;

    for (int j = t; j <= et; j++) {
        printf("%d ", A[s][j]);
    }

    for (int i = s+1; i <= es; i++) {
        printf("%d ", A[i][et]);
    }

    if (m > 1) {
        //矩阵才遍历第3条边,退化成一维数组不遍历
        for (int j = et-1; j >= t; j--) {
            printf("%d ", A[es][j]);
        }
    }

    if (n > 1) {
        //矩阵才遍历第4条边,退化成一维数组不遍历
        for (int i = es-1; i > s; i--) {
            printf("%d ", A[i][t]);
        }
    }

    walk_recursive(s+1, t+1, m-2, n-2);
}

void walk()
{
    walk_recursive(0, 0, M, N);
}

void init_data()
{
    int index = 1;

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = index;
            index += 1;
        }
    }
}

int main()
{
    init_data();
    walk();
    printf("\n");
}
