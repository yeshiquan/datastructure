#include <stdio.h>  
#include <string.h>  
  
char    pos[300];   /* pos[i] = j表示第i行上的皇后放在第j列 */  
int     n;  
int     count;  
  
/* 寻找第i行的皇后可以放的位置，不能放则令pos[row]等于-1 */  
void find (int row)  
{  
    int     i, j, k;  
    char    ok;  
  
    if (row == n) {  
        printf("第%d种解决方案: ", ++count);  
        for (k = 0; k < n; k++) {  
            printf("%d ", pos[k]);  
        }  
        printf("\n");  
        return;  
    }  
  
    /* 试探所有列 */  
    for (i = 0; i < n; i++) {  
        ok = 1; /* 先假设第i列可以放 */  
        for (j = 0; j < row; j++) {  /* 一旦检查到与放好的皇后攻击，则不让放 */  
            if (pos[j] == i || abs(pos[j]-i) == abs(j-row)) {  
                ok = 0;  
                break;  
            }  
        }  
        if (ok) {  
            pos[row] = i;  
            find(row+1);  
        }  
    }  
}  
  
int main()  
{  
    int     i, j;  
  
    while (scanf("%d", &n), n) {  
        count = 0;  
        find(0);  
    }  
}  
