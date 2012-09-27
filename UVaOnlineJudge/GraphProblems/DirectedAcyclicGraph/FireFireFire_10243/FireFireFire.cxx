/*
  Problem: Fire! Fire!! Fire!!!
  Link: http://uva.onlinejudge.org/external/102/10243.html
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: DP on trees. Find the vertex cover for the tree.
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

VVI G;
int memo[1010][2];
int visited[1010][2];
int level;
int minVertexCover(int prevVert, int curVert, int included) {
	int &res = memo[curVert][included];
	++level;
	if(res == -1) {
		if(G[curVert].size() == 0) // single vertex graph
			res = 1;
		else if(G[curVert].size() == 1 && G[curVert][0] == prevVert) // leaf
			if(included) res = 1; 
			else res = 0; 
		else {
			if(included) res = 1;
			else res = 0;
			REP(i, G[curVert].size()) {
				if(G[curVert][i] != prevVert) {
					if(!included) res += minVertexCover(curVert, G[curVert][i], 1);
					else res += min(minVertexCover(curVert, G[curVert][i], 1),
									minVertexCover(curVert, G[curVert][i], 0));
				}
			}
		}
	}
	--level;
	//REP(i, level) printf("    ");

	//printf("(%d %d %d)\n", curVert, included, res);
	
	return res;
}

void solveFireFireFire() {
	int N, sizeRow, val, total;
	while(scanf("%d", &N) != EOF && N > 0) {
		G.assign(N, VI());
		REP(i, N) { 
			scanf("%d", &sizeRow); 
			REP(j, sizeRow) {
				scanf("%d", &val);
				G[i].push_back(val-1);
			}
		}
		SET(memo, -1);
		SET(visited, 0);
		//printf("%d %d\n", minVertexCover(0, 0, 1), minVertexCover(0, 0, 0));
		total = min(minVertexCover(0, 0, 1), minVertexCover(0,0, 0));
		printf("%d\n", total);
	}
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	// solve something here
	solveFireFireFire();

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
