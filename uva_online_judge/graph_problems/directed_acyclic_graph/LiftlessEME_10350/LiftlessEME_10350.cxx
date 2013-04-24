/*
  Problem: Liftless EME
  Link: http://uva.onlinejudge.org/external/103/10350.html
  Author: Deepak 'deebee' Antony
  Solution: find the shortest path in the DAG :)
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

typedef long long LL;
typedef unsigned long long UL;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<LL> VL;
typedef vector<VL> VVL;
typedef pair<int,int> PII;
typedef vector<PII> VPII;
typedef vector<VPII> VVPII;

#define REP(i, n) for(int i = 0; i < (n); ++i)
#define FOR(i, st, nd) for(int i = (st); i < (nd); ++i)
#define SET(a, val) memset(a, val, sizeof(a))
#define mp make_pair

#define INF numeric_limits<int>::max()

VVPII G;
VI memo;

// DP for shortest path
int sl(int u) {
	if(memo[u] != -1) return memo[u];
	if(G[u].size() == 0) return memo[u] = 0;
	int shortest = INF;
	REP(i, G[u].size()) 
		shortest = min(shortest, G[u][i].second + sl(G[u][i].first));
	return memo[u] = shortest;
}

int shortestLength(int mHoles) {
	int shortest = INF;
	memo.assign(G.size(), -1);
	REP(i, mHoles)
		if(memo[i]==-1) shortest = min(shortest, sl(i));
	return shortest;
}

void solveLiftlessEME() {
	char name[20];
	int nRoofs, mHoles, entry;
	while(scanf("%s%d%d", name, &nRoofs, &mHoles) != EOF) {
		G.assign(mHoles*nRoofs, VPII());
		REP(floor, nRoofs-1) REP(hole, mHoles) REP(nextHole, mHoles) {
			scanf("%d", &entry);
			G[floor*mHoles + hole].push_back(mp((floor+1)*mHoles+nextHole, entry+2));
		}
		printf("%s\n%d\n", name, shortestLength(mHoles));
		// REP(node, G.size()) {
		// 	printf("%d: ", node);
		// 	REP(hole, G[node].size()) 
		// 		printf(" (%d %d) ", G[node][hole].first, G[node][hole].second);
		// 	printf("\n");
		// }
		// printf("\n");
	}
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	// solve something here
	solveLiftlessEME();

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
