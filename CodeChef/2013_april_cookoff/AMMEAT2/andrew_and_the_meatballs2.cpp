/*
  Problem: andrew and the meatballs 2
  Link: http://www.codechef.com/COOK33/problems/AMMEAT2
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: just list the multiples of 2
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

int k_plates[777];

void solve_andrew_and_the_meatballs()
{
	int T; scanf("%d", &T);

	while(T--)
	{
		LL N, K; scanf("%lld %lld", &N, &K);

		if( N == 1 )
		{
			printf("1\n");
		}
		else if( K > (N>>1) )
		{
			printf("-1\n");
		}
		else
		{
			int i = 0;
			for( ; i < (K-1); ++i)
			{
				printf("%d ", 2*(i+1));
			}
			printf("%d\n", 2*(i+1));
		}
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
