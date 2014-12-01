/*
  Problem: Maximizing XOR
  Link: https://www.hackerrank.com/challenges/maximizing-xor
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: use memoization
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

int dp_maximizing_xor( VVI &xors, int L, int R )
{
	if( xors[L][R] != -1 )
		return xors[L][R];

	if( L == R  || ( L == (R-1) ) || ( R == (L-1) ) )
		xors[L][R] = L ^ R; 
	else 
	{
		dp_maximizing_xor( xors, L, R-1 );
		dp_maximizing_xor( xors, L+1, R );
		xors[L][R] = std::max( xors[L][R-1] , xors[L+1][R] );
		xors[L][R] = std::max( L ^ R, xors[L][R] );
	}	

	return xors[L][R];
}

void solve_maximizing_xor()
{
	VVI xors;
	int L, R;

	xors.assign( 1001, VI( 1001, -1 ) );
	
	// while
	if( scanf("%d %d", &L, &R) != EOF )
	{
		printf( "%d\n", dp_maximizing_xor( xors, L, R ) );
	}
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	// solve something here
	solve_maximizing_xor();

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
