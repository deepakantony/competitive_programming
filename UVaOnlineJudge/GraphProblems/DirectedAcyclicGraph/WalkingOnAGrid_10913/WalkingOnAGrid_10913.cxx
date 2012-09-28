/*
  Problem: Walking On A Grid
  Link: http://uva.onlinejudge.org/external/109/10913.html
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: Sort of like finding the longest path but with a restriction. Add
  the restriction as a variable in the DP.
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

#define INF 1000000000000

int N, K;
int grid[75][75];
LL memo[75][75][6];
int visited[75][75];
int level;

LL maxPath(int row, int col, int kLeft) {
	if(kLeft < 0) return -INF;

	REP(i, level) printf("\t");
	printf("%d %d %d\n", row, col, kLeft);	
	++level;
	visited[row][col] = 1;
	LL &res = memo[row][col][kLeft];
	if(res == -(INF+1)) {
		if(kLeft == 0 && grid[row][col] == -1) res = -INF;
		else if(row == N-1 && col == N-1) res = grid[row][col];
		else {
			res = grid[row][col];
			if(res < 0) --kLeft;
			LL maximumRes = -INF;
			if(col > 0 && visited[row][col-1] == 0) 
				maximumRes = max(maximumRes, maxPath(row, col-1, kLeft));
			if(col < N-1 && visited[row][col+1] == 0)
				maximumRes = max(maximumRes, maxPath(row, col+1, kLeft));
			if(row < N-1 && visited[row+1][col] == 0)
				maximumRes = max(maximumRes, maxPath(row+1, col, kLeft));
			if(res < 0) ++kLeft;
			if(maximumRes <= -INF) res = -INF;
			else res += maximumRes;
		}
	}
	visited[row][col] = 0;
	--level;
	REP(i, level) printf("\t");
	printf("%d %d %d %lld\n", row, col, kLeft, res);

	return res;
}


void solveWalkingOnAGrid() {
	int test = 1;
	while(scanf("%d%d", &N, &K) != EOF && N > 0) {
		REP(i, N) REP(j, N) scanf("%d", &grid[i][j]);
		REP(i, N) REP(j, N) REP(k, K+1) memo[i][j][k] = -INF-1;
		LL res = maxPath(0, 0, K);
		if(res <= -INF) printf("Case %d: impossible\n", test++);
		else printf("Case %d: %lld\n", test++, res);
	}
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	// solve something here
	solveWalkingOnAGrid();

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
