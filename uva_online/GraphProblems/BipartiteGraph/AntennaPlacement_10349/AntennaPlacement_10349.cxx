/*
  Problem: Antenna Placement
  Link: http://uva.onlinejudge.org/external/103/10349.html
  Author: deebee
  Solution: bipartite graph
*/

#include <cstdio>
#include <cstring>
#include <cassert>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long LL;
typedef unsigned long long UL;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<LL> VL;
typedef vector<VL> VVL;

#define REP(i, n) for(int i = 0; i < (n); ++i)
#define FOR(i, st, nd) for(int i = (st); i < (nd); ++i)
#define SET(a, val) memset(a, val, sizeof(a))

void solve_10349() {
	int T; scanf("%d", &T);
	char inp[45][15];
	int h, w;
	while(T--) {
		scanf("%d%d", &h, &w);
		REP(row, h) scanf("%s", inp[row]);

		
	}
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	// solve something here

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
