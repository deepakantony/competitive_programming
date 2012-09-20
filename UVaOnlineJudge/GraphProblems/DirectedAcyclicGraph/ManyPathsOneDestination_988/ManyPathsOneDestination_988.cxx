/*
  Problem: Many Paths, One Destination
  Link: http://uva.onlinejudge.org/external/9/988.html
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: DP list all possible paths in the DAG
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

VVL G;
VL memo;

// DP for number of paths
LL np(int u){ 
	if(memo[u] != -1) return memo[u];
	if(G[u].size()==0) return memo[u] = 1;
	LL res = 0;
	REP(i, G[u].size())
		res += np(G[u][i]);
	return memo[u] = res;
}

LL numberOfPaths() {
	memo.assign(G.size(), -1);

	return np(0);
}

// solve many paths one destination problem
void solveMPOD() {
	int nEvents, nChoices;
	int nextChoice;
	bool first = true;
	while(scanf("%d", &nEvents) != EOF) {
		if(!first) printf("\n"); else first = false;
		G.assign(nEvents, VL());
		REP(u, nEvents) {
			scanf("%d", &nChoices);
			REP(v, nChoices) 
				scanf("%d", &nextChoice), G[u].push_back(nextChoice);
		}
		printf("%lld\n", numberOfPaths());
	}
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	// solve something here
	solveMPOD();

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
