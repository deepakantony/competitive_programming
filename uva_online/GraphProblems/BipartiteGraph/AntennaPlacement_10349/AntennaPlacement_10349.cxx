/*
  Problem: Antenna Placement
  Link: http://uva.onlinejudge.org/external/103/10349.html
  Author: deebee
  Solution: find maximum independent set in bipartite graph
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

// Global variables
VVI G;
VI left, owner, visited;
int h, w, totalEffective;

// convert "row" and "col" to graph nodes
inline int convertToGraphNode(int row, int col) { return row*w+col; }

int augment(int l) {
	// avoid cycles
	if(visited[l]) return 0;
	visited[l] = 1;
	REP(i, G[l].size()) {
		int v = G[l][i];
		if(owner[v] == -1 || augment(owner[v])) {
			owner[v] = l;
			return 1;
		}
	}
	return 0;
}

int maxCardinality() {
	int cardinality = 0;
	owner.assign(G.size(), -1);
	REP(l, left.size()) {
		visited.assign(G.size(), 0);
		cardinality += augment(left[l]);
	}
	return cardinality;
}

int maximumIndependentSet() {
	return totalEffective-maxCardinality();
}

void solve_10349() {
	int T; scanf("%d", &T);
	char inp[45][15];

	while(T--) {
		scanf("%d%d", &h, &w);
		REP(row, h) scanf("%s", inp[row]);

		totalEffective = 0;
		REP(row, h) REP(col, w) if(inp[row][col] == '*') ++totalEffective;
		
		G.clear(); G.assign(h*w, VI());
		REP(row, h) {
			for(int col = row%2 ? 1: 0; col < w; col+=2) {
				if(inp[row][col] == '*') {
					if(row > 0 && inp[row-1][col] == '*') 
						G[convertToGraphNode(row,col)]
							.push_back(convertToGraphNode(row-1,col));
					if(col > 0 && inp[row][col-1] == '*')
						G[convertToGraphNode(row, col)]
							.push_back(convertToGraphNode(row, col-1));
					if(row < (h-1) && inp[row+1][col] == '*')
						G[convertToGraphNode(row, col)]
							.push_back(convertToGraphNode(row+1, col));
					if(col < (w-1) && inp[row][col+1] == '*')
						G[convertToGraphNode(row, col)]
							.push_back(convertToGraphNode(row, col+1));
				}
			}
		}
		left.clear();
		REP(i, G.size()) if(G[i].size() > 0) left.push_back(i);
		
		printf("%d\n", maximumIndependentSet());
	}
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
	//freopen("Input_AntennaPlacement.txt", "r", stdin);
#endif 
	// solve something here
	solve_10349();
#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
