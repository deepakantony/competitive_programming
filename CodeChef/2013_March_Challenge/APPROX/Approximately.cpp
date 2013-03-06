/*
  Problem: Approximately
  Link: http://www.codechef.com/MARCH13/problems/APPROX
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: just repeat the division algorithm from middle school
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

void prepare_decimal_array(int *decimal_array)
{
	int numerator = 10*(103993%33102);
	int denominator = 33102;
	int decimal_index;

	REP(decimal_index, 1000000)
	{
		decimal_array[decimal_index] = numerator / denominator;
		numerator = 10 * (numerator % denominator);
	}
}

void solve_approximately()
{
	int decimal_array[1000000];
	prepare_decimal_array(decimal_array);

	int n_tests, test;
	int n_decimals, decimal_index;

	scanf("%d", &n_tests);

	REP(test, n_tests)
	{
		scanf("%d", &n_decimals);

		printf("3");
		REP(decimal_index, n_decimals)
		{
			if(decimal_index == 0)
			{
				printf(".");
			}
			printf("%d", decimal_array[decimal_index]);
		}

		printf("\n");
	}
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	solve_approximately();

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
