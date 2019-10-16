#include <stdio.h>
#include <string.h>

//#define DEBUG

#ifdef DEBUG
#define debug(...) printf( __VA_ARGS__) 
#else
#define debug(...)
#endif

#define max(a,b) (a) > (b) ? (a) : (b)

#define N 250

int 	c[N][N];

int lcs(char *s1, char *s2)
{
	int		i, j, n, m;

	n = strlen(s1);
	m = strlen(s2);

	for (i = 1; i <= n; i++) {
		for (j = 1; j <= m; j++) {
			if (s1[i-1] == s2[j-1]) {
				c[i][j] = c[i-1][j-1] + 1;
			}
			else {
				c[i][j] = max(c[i][j-1], c[i-1][j]);
			}
			debug("c[%d][%d] = %d\n", i, j, c[i][j]);
		}
	}

	return c[n][m];
}

int main()
{
	char 	s1[N], s2[N];

	while (scanf("%s%s", s1, s2) != EOF) {
		debug("%s %s\n", s1, s2);
		printf("%d\n", lcs(s1, s2));
	}
	return 0;
}
