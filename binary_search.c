/**
 * 二分查找
 * @author: yeshiquan@gmail.com
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * 二分查找给定的元素
 * @A 数组的指针
 * @len 数组的长度
 * @e 查找的元素
 * @return 成功返回元素所在的下标，否则返回-1
 */
int binary_search(int *A, int len, int e)
{
    int m, s, t;
    
    s = 0; 
    t = len - 1;

    while (s <= t) {
        m = (s + t) / 2;
        if (A[m] > e) {
            t = m - 1;
        } else if (A[m] < e) {
            s = m + 1;
        } else {
            return m;
        }
    }

    return -1;
}

int main () 
{
    int A[] = {1,3,4,9,15,20,37,41,59,60};
    int pos = binary_search(A, 10, 37);
    printf("%d\n", pos);
}
