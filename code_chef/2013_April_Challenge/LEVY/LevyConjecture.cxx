/*
  Problem: Levy Conjecture
  Link: http://www.codechef.com/APRIL13/problems/LEVY
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: pre calculate the solution for all n in 1 to N
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

void prepare_levy_conjecture_n( int *levy_conjecture_array, int array_size )
{

}

void levy_conjecture()
{
	int levy_conjecture_array[ 10001 ];
	prepare_levy_conjecture_n( levy_conjecture_array, 10000 );

	int num_tests;
	int test;
	int N;

	scanf("%d", &num_tests);

	REP( test, num_tests )
	{
		scanf("%d", &N);
		printf("%d\n", levy_conjecture_array[ N ] );
	}
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	// solve something here
	solve_levy_conjecture();

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
