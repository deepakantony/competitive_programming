/*
  Problem: Factors and Multiples
  Link: http://uva.onlinejudge.org/external/111/11159.html
  Author: deebee
  Solution: bipartite matching; ans is maximum cardinality
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
VI A;
VI owner, visited;

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

int maxCardinality() {
	owner.assign(G.size(), -1);
	int cardinality = 0;
	REP(left, A.size()) {
		visited.assign(G.size(), 0);
		cardinality += augmentingPath(left);
	}
	return cardinality;
}

int readInput() {
	int n, m, val;
	scanf("%d", &n);
	A.clear();
	REP(i, n) scanf("%d", &val), A.push_back(val);
	scanf("%d", &m);
	G.assign(n+m, VI());
	REP(i, m) {
		scanf("%d", &val);
		REP(j, A.size()) 
			if((A[j] == 0 && val == 0) || (A[j] != 0 && val%A[j] == 0))
				G[j].push_back(n+i);
	}
}

void solveFactorsAndMultiples() {
	int T; scanf("%d", &T);
	REP(test, T) {
		readInput();
		printf("Case %d: %d\n", test+1, maxCardinality());
	}
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	// solve something here
	solveFactorsAndMultiples();
#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
