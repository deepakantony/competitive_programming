/*
  Problem: Game of thrones
  Link: https://www.hackerrank.com/challenges/game-of-thrones
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: len(string) == even ? all letters should have a double : else all letters but one should have a double
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

#include <bitset>

void solve_game_of_thrones()
{
	char inp_string[100001];
	while( scanf("%s", inp_string ) != EOF )
	{
		int len = strlen(inp_string);
		
		char *ch = inp_string;
		bitset<26> char_slots;
	
		while( *ch )
		{
			char_slots[ (*ch) - 'a' ].flip();
			++ch;
		}

		if( char_slots.count() == 0 || char_slots.count() == 1 )
			printf("YES\n");
		else
			printf("NO\n");
	}
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	// solve something here
	solve_game_of_thrones();

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
