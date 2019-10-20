#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
  
#define DEBUG  
  
#ifdef DEBUG  
#define debug(...) printf( __VA_ARGS__)   
#else  
#define debug(...)  
#endif  

// 查找数组中是否有两个数之和等于指定值
// 首先，将数组排序。 比如排序后得到的数组a是：-2 -1 0 3 5 6 7 9 13 14。
// 然后使用low和high 两个下标指向数组的首尾元素。如果a[low]+a[high] > 
// sum，那么说明a[high]
// 和数组中的任何其它一个数的和都一定大于sum(因为它和最小的a[low]相加都大于s
// um)。 因此，a[high]不会与数组中任何一个数相加得到sum，于是我们可以直接不
// 要它， 即让high向前移动一位。同样的，如果a[low]+a[high] < 
// sum，那么说明a[low] 
// 和数组中的任何其它一个数的和都一定小于sum(因为它和最大的a[high]相加都小于
// sum)。 因此，我们也可以直接不要它，让low向前移动一位。如果a[low]+a[high]
// 等于sum， 则输出。当low小于high时，不断地重复上面的操作即可。

#define N 7

int a[N] = {1,3,4,5,6,8,10};
int SUM = 7;

void gen_two_number()
{
    int low = 0;
    int high = N-1;

    while (low < high) {
        int sum = a[low] + a[high];
        if (sum > SUM) {
            high--;
        } else if (sum < SUM) {
            low++;
        } else {
            printf("%d %d\n", a[low], a[high]);
            low++; high--;
        }
    }
}
  
int main()  
{  
    gen_two_number();
    return 1;
}  
