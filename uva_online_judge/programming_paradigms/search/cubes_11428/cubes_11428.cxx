/*
  Problem: Cubes
  Link: http://uva.onlinejudge.org/external/114/11428.html
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: Make a lookup table for all N's with their corresponding x and y.
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
#define CUBE(x) ((x)*(x)*(x))

VPII lookup_table;

void prepare_lookup_table()
{
	lookup_table.assign(10010, mp(0, 0));

	int x = 2, y = 1;
	for(; ( CUBE(y) - CUBE(y-1) ) <= 10000; ++y)
	{
		for( x = y+1; ( CUBE(x) - CUBE(y) ) <= 10000; ++x)
		{
			if( lookup_table[ CUBE(x) - CUBE(y) ].first == 0 )
				lookup_table[ CUBE(x) - CUBE(y) ] = mp(x, y);
		}
	}
}


void solve_cubes()
{
	prepare_lookup_table();

	int N;

	while( scanf("%d", &N) != EOF && N != 0 )
	{
		if( lookup_table[N].first == 0 )
			printf("No solution\n");
		else
			printf("%d %d\n", lookup_table[N].first, lookup_table[N].second);
	}
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	solve_cubes();

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
