#include <cstdio>
#include <cstring>
#include <ctime>
#include <algorithm>

using namespace std;

int memo[1501][1501];
int kays[1501][1501];
char P[1501], Q[1501];
int N, K;

int diff(int pi, int qj, int n)
{
	int res = 0;
	for(int i = 0; i < n; ++i)
		if(P[i+pi] != Q[i+qj])
			res++;
	return res;
}

int maxL()
{
	if (N == K) return N;
	int L = K; // the maxL has to be atleast K
	// initialize 
	int limit = N-K;
	for(int i = 0; i <= limit; ++i) {
		memo[i][limit] = memo[limit][i] = K;
		kays[i][limit] = K - diff(i, limit, K);
		kays[limit][i] = K - diff(limit, i, K);
	}

	for(int i = limit-1; i >= 0; i--)
		for(int j = limit-1; j >= 0; j--) 
		{
			int prev = memo[i+1][j+1];
			int prevKay = kays[i+1][j+1];
			if(P[i] == Q[j] || P[i+prev] == Q[j+prev]) {
				memo[i][j] = 1+prev;
				kays[i][j] = prevKay;
			}
			else if(prevKay == 0) {
				memo[i][j] = prev;
				kays[i][j] = 0;
			}
			else {
				memo[i][j] = prev;
				kays[i][j] = prevKay -1;
			}
			L = max(L, memo[i][j]);
		}

	return L;
}

int main(int argc, char *argv[])
{
	clock_t start = clock();

	int nTests; scanf(" %d", &nTests);
	while(nTests--) {
		scanf(" %d %s %s", &K, P, Q);
		N = strlen(P);
		printf("%d\n", maxL());
	}

	fprintf(stderr, "Time taken: %.3f\n", 
			((double)(clock()-start))/CLOCKS_PER_SEC);
}
