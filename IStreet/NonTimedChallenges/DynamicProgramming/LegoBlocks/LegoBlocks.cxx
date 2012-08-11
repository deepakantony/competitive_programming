#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ctime>

using namespace std;

typedef long long LL;

#define REP(i, n) for(int i = 0; i < (n); ++i)
#define FOR(i, st, nd) for(int i = (st); i < (nd); ++i)
#define MOD 1000000007

LL singleRow[1000];
LL allrow[1000][1000];
LL memo[1000];

inline LL MODMUL(LL x, LL y){
	return (x*y)%MOD;
}

LL modularPow(LL base, LL exponent) {
	LL res = 1;
	while(exponent > 0) {
		if(exponent % 2 == 1) res = MODMUL(res, base);
		exponent = exponent >> 1;
		base = MODMUL(base, base);
	}
	return res;
}


void preCalculate() {
	memset(singleRow, 0, sizeof singleRow);
    // First calculate how many ways can we build a wall with just one row,
    // including breakable ones.
    REP(x, 4) singleRow[x] = 1;
	FOR(x, 1, 1000) REP(i, min(4,x))
		singleRow[x] = (singleRow[x] + singleRow[x-1-i])% MOD;
	
	// Now calculate the number of ways in which we can build the wall with N
    // rows. This is calculated by x^N, where x is the number of ways we can build
    // a wall in single row. This includes breakable ones.
	REP(N, 1000) REP(i, 1000)
		allrow[N][i] = modularPow(singleRow[i], N+1);
}

LL unbreakableLegoBlocks(int  N, int M) {
    // Now we need to subtract from this, the number of ways to create breakable
    // walls. So, for each wall of width M, we have total number of ways to 
    // create a wall with height N; this is done with the observation that, to
    // build a wall with size i < M, we have nrow[i] ways to do it and also to
    // build a wall with size M-i we have nrow[M-i] ways to do it. Totally, a 
    // wall which can be split at i can be created in nrow[i]*nrow[M-i] ways.
    // So for every i < M subtract nrow[i]*nrow[M-i] from it to get the number
    // of ways to build unbreakable wall.

    LL *nrow = allrow[N-1];
	
	REP(index, M) {
		memo[index] = nrow[index];
		REP(i, index) {
			memo[index] = (memo[index] - (memo[i]*nrow[index-i-1])%MOD)%MOD;
			if(memo[index] < 0) memo[index] = MOD+memo[index];
		}
	}
	return memo[M-1];
}

int main(int argc, char *argv[]) {
    clock_t start = clock();
	preCalculate();
	int T; scanf("%d", &T);
	int M, N;
	while(T--) {
		scanf(" %d %d", &N, &M);
		printf("%lld\n", unbreakableLegoBlocks(N,M));
	}
	fprintf(stderr, "Time taken: %.3f secs\n", (clock()-start)/(float)CLOCKS_PER_SEC);
	return 0;
}

