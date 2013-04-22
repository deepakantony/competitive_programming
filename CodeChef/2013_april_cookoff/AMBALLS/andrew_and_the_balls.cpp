/*
  Problem: Template CPP main file.
  Link:
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: DONT KNOW
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

int C[200];

LL dp(k

void solve_amballs()
{
	int T; scanf("%d", &T);


	while(T--) 
	{
		int N; scanf("%d", &N);
		REP(i, N) 
		{
			scanf("%d", &C[i]);
		}
	}
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	solve_amballs();

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
