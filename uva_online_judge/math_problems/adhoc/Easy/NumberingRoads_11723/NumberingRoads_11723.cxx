/*
  Problem: Template CPP main file.
  Link: http://uva.onlinejudge.org/external/117/11723.html
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: if R/N > 26 then impossible else R/N
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

void solveNumberingRoads()
{
	int N, R;
	int caseNum = 0;

	while( scanf( "%d%d", &R, &N ) != EOF && R != 0 && N != 0 )
	{
		printf( "Case %d: ", ++caseNum );

		if ( (R/N) > 26 ) 
			printf( "impossible\n" );
		else
			printf( "%d\n", (R-1)/N );
	}
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	// solve something here
	solveNumberingRoads();

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
