/*
  Problem: Template CPP main file.
  Link:
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: 
*/

#include <cstdio>
#include <cstring>
#include <cassert>
#include <ctime>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits>
#include <functional>

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

void solve_andrew_and_the_meatballs()
{
	int T; scanf("%d", &T);
	LL P[7];

	while(T--)
	{
		LL N, M; scanf("%lld %lld", &N, &M);

		REP(i, N) scanf("%lld", &P[i]);

		int min_plates = 0;

		sort( P, P+N, greater<LL>() );

		REP(i, N)
		{
			if(M <= 0) break;

			++min_plates;
			M -= P[i];
		}

		if( M > 0 ) min_plates = -1;

		printf("%d\n", min_plates);
	}
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	solve_andrew_and_the_meatballs();

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
