/*
  Problem: Coin flip
  Link: http://www.codechef.com/NOV12/problems/CONFLIP
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: if N is even, the answer is N/2 for both H/T. If N is odd, the ans
  is N/2 for the starting face while (N/2)+1 for non starting face.
*/

#include <cstdio>
#include <cstring>
#include <cassert>
#include <ctime>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits>

using namespace std;

typedef unsigned long long UL;
typedef long long LL;
typedef pair<int,int> PII;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<LL> VL;
typedef vector<VL> VVL;
typedef vector<PII> VPII;
typedef vector<VPII> VVPII;

#define REP(i, n) for(int i = 0; i < (n); ++i)
#define FOR(i, st, nd) for(int i = (st); i < (nd); ++i)
#define SET(a, val) memset(a, val, sizeof(a))
#define mp make_pair

#define INF numeric_limits<int>::max()

void solveCoinFlip()
{
	int T; scanf("%d", &T);
	int G, N, I, Q;
	while(T--) {
		scanf("%d", &G);
		while(G--) {
			scanf("%d%d%d", &I, &N, &Q);
			if((N&1) == 0) // even
				printf("%d\n", N>>1); // ans is N/2
			else //odd
				if(I == Q) printf("%d\n", N>>1); //ans is N/2
				else printf("%d\n", (N>>1)+1); // ans is (N/2)+1
		}
	}
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	solveCoinFlip();

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}

