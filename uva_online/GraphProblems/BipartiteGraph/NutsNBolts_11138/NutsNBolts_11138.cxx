/*
  Problem: Nuts N Bolts
  Link: http://uva.onlinejudge.org/external/111/11138.html
  Author: deebee
  Solution: find the maximum cardinality for this bipartite graph
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

VVI G;

VI visited, owner;
int nBolts, nNuts;

int augmentingPath(int left) {
	if(visited[left]) return 0;
	visited[left] = 1;
	REP(i, G[left].size()) {
		int v = G[left][i];
		if(owner[v] == -1 || augmentingPath(owner[v])) {
			owner[v] = left;
			return 1;
		}
	}
	return 0;
}

// return the maximum cardinality 
int mcbm() {
	owner.assign(nBolts+nNuts, -1);
	int cardinality = 0;
	REP(left, nBolts) {
		visited.assign(nBolts+nNuts, 0);
		cardinality += augmentingPath(left);
	}
	return cardinality;
}

// solve this problem
void solveNutsNBolts() {
	int T; scanf("%d", &T);
	int u;
	REP(test, T) {
		scanf("%d%d",&nBolts, &nNuts);
		G.assign(nBolts+nNuts, VI());
		REP(row, nBolts) REP(col, nNuts) {
			scanf("%d", &u); if(u) G[row].push_back(nBolts+col);
		}

		printf("Case %d: a maximum of %d nuts and bolts can be fitted together\n",
			   test+1, mcbm());
	}
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	// solve something here
	solveNutsNBolts();

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
