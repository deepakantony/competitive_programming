/*
  Problem: Brick Game
  Link: http://uva.onlinejudge.org/external/118/11875.html
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: Just print the middle element.
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

void solveBrickGame()
{
	int T; scanf("%d", &T);
	REP(test, T) {
		int nPlayers; scanf("%d", &nPlayers);
		int captainIndex = nPlayers/2;
		int age;
		printf("Case %d: ", test+1);
		REP(p, nPlayers) {
			scanf("%d", &age);
			if(p == captainIndex)
				printf("%d\n", age);
		}
	}
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	// solve something here
	solveBrickGame();

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
