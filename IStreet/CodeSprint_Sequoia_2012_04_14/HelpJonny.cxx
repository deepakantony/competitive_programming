#include <cstdio>
int main(int argc, char *argv[])
{
	int T, N; scanf(" %d", &T);
	while(T--) {
		scanf(" %d", &N);
		if(N%4==0 || N%4==1)
			printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
