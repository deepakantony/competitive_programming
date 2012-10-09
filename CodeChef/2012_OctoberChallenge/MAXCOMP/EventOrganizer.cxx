/*
  Problem: Event Organizer
  Link: http://www.codechef.com/OCT12/problems/MAXCOMP
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: Create the DAG and find the longest path in this graph.
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
#define GRAPH_SIZE 49

int G[50][50];
LL memo[50];

LL longestPath(int curNode) {
	if(memo[curNode] == -1) {
		memo[curNode] = 0;
		FOR(i, curNode+1, GRAPH_SIZE) {
			memo[curNode] = max(memo[curNode], G[curNode][i] +
						  longestPath(i));
		}
	}
	return memo[curNode];
}

void solveEventOrganizer() {
	int T; scanf("%d", &T);
	int N, u, v, w;
	while(T--) {
		SET(G, 0);
		scanf("%d", &N);
		while(N--) {
			scanf("%d %d %d", &u, &v, &w);
			G[u][v] = max(G[u][v], w);
		}

		SET(memo, -1);
		//LL lp = 0;
		//REP(i, G.size()) if(memo[i] == -1) lp = max(lp, longestPath(i));
		printf("%lld\n", longestPath(0));
	}
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	// solve something here
	solveEventOrganizer();

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
