/*
  Problem: Template CPP main file.
  Link: http://uva.onlinejudge.org/external/107/10773.html
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: if u <= v then "can't determine" else if shortest time then it's d/u secs or if shortest distance then it's d/sqrt(u^2-v^2) secs.
*/

#include <cstdio>
#include <cstring>
#include <cassert>
#include <ctime>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits>
#include <cmath>

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

void solveBackToIntermediateMath()
{
	int N;
	float d, v, u;
	scanf( "%d", &N );

	REP(i, N)
	{
		scanf( "%f%f%f", &d, &v, &u );
		
		printf( "Case %d: ", i + 1 );
		if( u <= v || u == 0.f || v == 0.f || d == 0.f )
			printf( "can\'t determine\n" );
		else 
		{
			printf( "%.3f\n", fabs((d/u) - (d/sqrt(u*u-v*v))));
		}
	}
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	// solve something here
	solveBackToIntermediateMath();

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
