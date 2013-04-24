/*
  Problem: ProjectScheduling
  Link: http://uva.onlinejudge.org/external/4/452.html
  Author: deebee
  Solution: find the longest path in the DAG -> topological sort & longest path
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
VI nodeTime;
VI memo;

// DP for longest path
// lp(i) = max(time(i) + lp(j)) for every j adjacent to vertex i
// lp(i) = time(i) when there are no adjacent vertex to i
int lp(int u) {
	if(memo[u] != -1) return memo[u];
	if(G[u].size() == 0) return memo[u] = nodeTime[u];
	int res = 0;
	REP(i, G[u].size()) 
		res = max(res, lp(G[u][i]));
	return memo[u] = res + nodeTime[u];
}

int longestPath() {
	// find the longest path
	memo.assign(nodeTime.size(), -1);
	int res = 0;
	REP(i, nodeTime.size()) 
		if(memo[i] == -1) res = max(res,lp(i));

	return res;
}

void readInput() {
	char inp[100];
	char curN; int t; char nodes[50];
	G.assign(26, VI());
	nodeTime.assign(26, 0);
	while( fgets(inp, 100, stdin) != NULL && inp[0] != 0 && inp[0] != '\n') {
		int count = sscanf(inp, "%c %d %s",&curN, &t, nodes);
		int v = curN - 'A';
		nodeTime[v] = t;

		if(count == 3) 
			for(int i = 0; nodes[i]; ++i)
				G[nodes[i]-'A'].push_back(v);
	}
	//REP(i, nodeTime.size()) printf("%d ", nodeTime[i]); printf("\n");
}

void solveProjectScheduling() {
	int T; scanf("%d\n", &T);
	
	while(T--) {
		scanf("\n");
		readInput();
		printf("%d\n", longestPath());
		if(T!=0) printf("\n");
	}
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	// solve something here
	solveProjectScheduling();

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
