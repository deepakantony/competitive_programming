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

int longestPath() {
	// find topological sort

	// find the longest path
	return 0;
}

void readInput() {
	char inp[100];
	char curN; int t; char nodes[50];
	G.assign(26, VI());
	nodeTime.assign(26, 0);
	while( scanf("%[\n]s", inp) != EOF && inp[0] != 0 && inp[0] != '\n') {
		sscanf(inp, "%c %d %s",&curN, &t, nodes);
		int v = curN - 'A';
		nodeTime[v] = t;
		for(int i = 0; nodes[i]; ++i)
			G[nodes[i]-'A'].push_back(v);
	}
}

void solveProjectScheduling() {
	int T; scanf("%d", &T);
	
	while(T--) {
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
