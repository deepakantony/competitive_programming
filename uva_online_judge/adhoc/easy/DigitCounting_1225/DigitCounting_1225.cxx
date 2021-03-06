/*
  Problem: Digit Counting
  Link: http://uva.onlinejudge.org/external/12/1225.html
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: for now simply loop through all N numbers
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

void solve_digit_counting()
{
	int n_tests;
	int count_digits[10];
	scanf("%d", &n_tests );
	while( n_tests-- )
	{
		SET(count_digits, 0);
		int seq_max;
		scanf("%d", &seq_max );

		REP(i, seq_max )
		{
			int cur_n = i + 1;

			while( cur_n > 0 )
			{
				count_digits[ cur_n % 10 ]++;
				cur_n /= 10;
			}
		}

		REP(i, 9)
		{
			printf("%d ", count_digits[i]);
		}
		printf("%d\n", count_digits[9] );
	}
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	solve_digit_counting();

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
