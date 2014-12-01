/*
  Problem: Utopian Tree
  Link: https://www.hackerrank.com/challenges/utopian-tree
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: used dp to solve this; we can also do a formula
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

void dp_utopian_tree( int *tree, int N )
{
	if( tree[N] != -1 )
		return;

	if( N == 0 )
	{
		tree[N] = 1;
	}
	else if( N%2 == 0 )
	{
		dp_utopian_tree( tree, N-1 );
		tree[N] = tree[N-1] + 1;
	}
	else
	{
		dp_utopian_tree( tree, N-1 );
		tree[N] = 2 * tree[N-1];
	}
}

void solve_utopian_tree()
{
	int T, N;
	int tree[100];

	memset( tree, -1, sizeof( tree ) );
	scanf("%d", &T);

	while(T--)
	{
		scanf("%d", &N);

		if( tree[N] == -1 )
			dp_utopian_tree(tree, N);

		printf( "%d\n", tree[N] );
	}
}

int main(int argc, char *argv[]) 
{
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	// solve something here
	solve_utopian_tree();

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
