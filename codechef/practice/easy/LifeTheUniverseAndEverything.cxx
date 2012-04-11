// Problem: Life, the universe and everything

#include <cstdio>
#include <cstdlib>

int main(int argc, char *argv[])
{
	int n;
	while(scanf("%d", &n) != EOF)
		if(n == 42)break;
		else printf("%d\n", n);
	return 0;
}
	
