/*
  Problem: Is fibo (i.e. is fibonacci number)
  Link: https://www.hackerrank.com/challenges/is-fibo
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: store fibonacci numbers updto 10^10 and search them.
*/

#include <cstdio>
#include <cstring>
#include <cassert>
#include <ctime>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits>
#include <set>

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

void solve_is_fibo()
{
	int T; 
	LL N;

	set<LL> fibonacci_numbers;
	LL fib0 = 0;
	fibonacci_numbers.insert(fib0);
	LL fib1 = 1;
	fibonacci_numbers.insert(fib1);
	while( fib1 < 10000000000 )
	{
		LL fib_new = fib0 + fib1;
		fibonacci_numbers.insert(fib_new);
		fib0 = fib1;
		fib1 = fib_new;
	}

	scanf("%d", &T);
	while(T--)
	{
		scanf("%lld", &N);
		if( fibonacci_numbers.find(N) != fibonacci_numbers.end() )
			printf("IsFibo\n");
		else
			printf("IsNotFibo\n");
	}
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	// solve something here
	solve_is_fibo();

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
