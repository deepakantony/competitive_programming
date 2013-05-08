/*
  Problem: Your name is mine
  Link: http://ww2.codechef.com/MAY13/problems/NAME2
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: simple string problem
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

bool is_subsequence(char *p_main_str, char *p_second_str)
{
	if(p_main_str == NULL || p_second_str == NULL)
		return false;
	while( *p_second_str && *p_main_str )
	{
		if( *p_second_str == *p_main_str )
			++p_second_str;

		++p_main_str;
	}

	if( *p_second_str ) return false;
	else return true;
}

void solve_your_name_is_mine()
{
	char man[25001], woman[25001];

	int test; scanf("%d", &test);
	while(test--)
	{
		scanf("%s", man);
		scanf("%s", woman);

		if( is_subsequence(man, woman) || is_subsequence(woman, man) )
			printf("YES\n");
		else
			printf("NO\n");
	}
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	solve_your_name_is_mine();

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
