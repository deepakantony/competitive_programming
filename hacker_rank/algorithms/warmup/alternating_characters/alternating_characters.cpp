/*
  Problem: Alternating characters
  Link: https://www.hackerrank.com/challenges/alternating-characters
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: loop through the string and if the characters are not alternating increment the count by 1
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

void solve_alternating_characters()
{
	int T;
	char str[100001];
	scanf("%d", &T);

	REP(i,T)
	{
		scanf("%s", str);

		int minimum_steps = 0;
		char prev = '\0';
		char *ptr = str;
		while( *ptr )
		{
			if( *ptr == prev )
			{
				++minimum_steps;
			}
			prev = *ptr;
			++ptr;
		}
		printf("%d\n", minimum_steps );
	}
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	solve_alternating_characters ();

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
