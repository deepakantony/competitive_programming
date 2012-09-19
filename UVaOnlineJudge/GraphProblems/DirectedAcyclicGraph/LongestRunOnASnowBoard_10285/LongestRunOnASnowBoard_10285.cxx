/*
  Problem: Longest Run On A Snowboard
  Link: http://uva.onlinejudge.org/external/102/10285.html
  Author: Deepak 'deebee' Antony
  Solution: Find the longest path in the DAG.
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
VI memo;

// DP for longest path in DAG
// lp(i) = 1+max(lp(j)) for all j adjacent to i
// lp(i) = 1 if no j's are adjacent to i
int lp(int u) {
	if(memo[u] != -1) return memo[u];
	if(G[u].size() == 0) return memo[u] = 1;
	int longest = 0;
	REP(i, G[u].size())
		longest = max(longest, lp(G[u][i]));
	return memo[u] = longest+1;
}
	

int longestPath() {
	memo.assign(G.size(), -1);
	int longest = 0;
	REP(i, memo.size())
		if(memo[i] == -1) longest = max(longest, lp(i));
	return longest;
}

void solveLongestRunOnASnowboard() {
	int T; scanf("%d", &T);
	char name[100];
	int R, C;
	int matrix[100][100];
	while(T--) {
		scanf("%s %d %d", name, &R, &C);
		REP(row, R) REP(col, C) scanf("%d", &matrix[row][col]);
		G.assign(R*C, VI());
		REP(row, R) REP(col, C) {
			if(row > 0 && matrix[row-1][col] < matrix[row][col])
				G[row*C+col].push_back( (row-1)*C + col );
			if(col > 0 && matrix[row][col-1] < matrix[row][col])
				G[row*C+col].push_back( row*C + col-1 );
			if(row < (R-1) && matrix[row+1][col] < matrix[row][col])
				G[row*C+col].push_back( (row+1)*C + col);
			if(col < (C-1) && matrix[row][col+1] < matrix[row][col])
				G[row*C+col].push_back(row*C + col + 1);
		}

		printf("%s: %d\n", name, longestPath());
	}
	
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	// solve something here
	solveLongestRunOnASnowboard();

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
