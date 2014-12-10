/*
  Problem: Angry children
  Link:https://www.hackerrank.com/challenges/angry-children
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: sort the list of candies; find the minimum difference between elements which are exactly k distance away.
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

void solve_angry_children()
{
	int N, K, candies[100001];

	while( scanf(" %d %d", &N, &K ) != EOF )
	{
		REP(i, N) scanf(" %d", &candies[i] );

		sort( candies, candies + N );
		
		int min_unfairness = INF;
		REP(i, N-K+1) 
			min_unfairness = min( min_unfairness, candies[i+K-1] - candies[i] );
		printf("%d\n", min_unfairness );
	}
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	// solve something here
	solve_angry_children();

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
