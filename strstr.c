#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
  
#define DEBUG  
  
#ifdef DEBUG  
#define debug(...) printf( __VA_ARGS__)   
#else  
#define debug(...)  
#endif  

char *_strstr(char *s1, char *s2)
{
    char *p;
    char *q;
    char *r;
    
    for (p = s1; *p != '\0'; p++) {
        for (q=s2, r=p; *q != '\0' && *r == *q; q++, r++);
        if (*q == '\0') {
            return p;
        }
    }

    return NULL;
}
  
int main()  
{  
    char *s1 = "abcdefgh";
    char *s2 = "cde";
    char *idx = _strstr(s1, s2);
    printf("%s\n", idx);
    return 1;
}  
