#include <cstdio>

typedef long long int LL;

int main(int argc, char *argv[])
{
	int nTests;
	scanf(" %d", &nTests);
	while(nTests--)
	{
		int N;
		scanf(" %d", &N);
		LL prodSum = 0;
		LL prevNum = 0;
		for(int i = 1; i <= N; i+=2) {
			prodSum += i*prevNum;
			prevNum = i;
		}
		for(int i = (N%2 == 0 ? N : N-1); i >= 2; i-=2) {
			prodSum += i*prevNum;
			prevNum = i;
		}
		if(N==1) printf("%d\n", N);
		else printf("%lld\n", prodSum);
	}
	return 0;
}
