/*
 * 搜索+回溯+剪枝
 */
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
  
#define DEBUG  
  
#ifdef DEBUG  
#define debug(...) printf( __VA_ARGS__)   
#else  
#define debug(...)  
#endif  
  
int     n;      /* 一共多少根小木棒数 */
int     len;    /* 每根原始木棒的长度 */
int     count;  /* 原始木棒一共多少根 */
char    found;  
int     stick[64];  /* 每根小木棒的长度 */
int     st[64];     /* st[k] = sum{a[k]...a[n-1]}, 某根木棒和所有比它短的木棒加起来的长度 */  
char    used[64];  
  
static int compare(const void *p1, const void *p2)  
{  
    return *((int *)p2) - *((int *)p1);  
}  

void print_array(int *a, int s, int t) 
{
    for (int i = 0; i <= t; i++) {
        debug("%d ", a[i]);
    }
    debug("\n");
}
  
/* 
 * 第k个小木棒开始搜索, sum:木棒还原好的长度, num: 已还原好的木棒数 
 * 其实是个填空题, s0,s1,sk-1,_,_,_,_,_,_ 其中s0,s1,sk-1是已经拼凑好的小木棒，搜索剩余的小木棒
 * */ 
void search(int k, int sum, int num)   
{  
    int     i, pre;  
  
    if (num == count) {  
        found = 1;  
        return;  
    }  
    if (sum == len) {  
        //还原下一根原始木棒, 从第0根小木棒开始拼凑
        search(0, 0, num+1);  
    } else {  
        //从第k跟木棒开始搜索，如果有一根木棒满足:  
        //1 未被使用  
        //2 长度跟上一次尝试失败的小木棒不一样
        //3 它的长度加上已拼凑好的长度不会超过原始长度  
        //4 sum加上它自己和所有比它短的木棒的长度必须超过原始长度  
        //则把这根木棒拼凑过去  
        pre_failed = -1; /* 上一根尝试失败的小木棒 */
        for (i = k; i < n; i++) {  
            debug("stick[i]=%d, pre_failed=%d\n", stick[i], pre_failed);
            if (!used[i] && stick[i] != pre_failed && sum+stick[i] <= len && sum+st[i] >= len) {    
                debug("选择%d加在第%d根木棒后面\n", stick[i], num+1);  
                used[i] = 1;  
                search(i+1, sum+stick[i], num);  
                if (found) return;  
                debug("否定%d\n", stick[i]);  
                used[i] = 0;
		pre_failed = stick[i];
                if (k == 0) {
                    // 此时如果最大的stick都尝试失败了，那后面更小的stick就更加失败, 不要浪费时间搜索了
                    debug("不要再试了\n");
                    break;
                }
			}  
        }  
    }  
}  
  
int main()  
{  
    int     i, j, k, sum;  
  
    while (scanf("%d", &n), n != 0) {  
        debug("=============================\n");
        sum = 0;  
        found = 0;  
        for (i = 0; i < n; i++) {  
            scanf("%d", stick+i);  
            sum += stick[i];  
        }  
        qsort(stick, n, sizeof(int), compare);  
		print_array(stick, 0, n-1);
        st[n-1] = stick[n-1];  
        for (i = n-2; i >= 0; i--) {  
            st[i] = st[i+1]+stick[i];  
        }  
        for (i = stick[0]; i <= sum; i++) {  
            if (sum % i == 0) {  
                len = i;  
                count = sum/i;  
                debug("----------每根木棒长度为%d, %d根木棒的搜索过程------------\n", i, count);  
                memset(used, 0, sizeof(used));  
                search(0, 0, 0);  
  
                debug("还原结果为: ");  
                for (k = 0; k < n; k++) {  
                    debug("%d ", used[k]);  
                }  
                debug("\n\n");  
  
                if (found) {  
                    break;  
                }  
            }  
        }  
        printf("%d\n", found? len : sum);  
    }  
    return 0;  
}  


/*
 * input.txt
9
5 2 1 5 2 1 5 2 1
4
1 2 3 4
14
5 2 2 2 4 4 3 2 2 3 4 3 3 3
9
5 5 2 5 5 2 5 5 2
0
*/
