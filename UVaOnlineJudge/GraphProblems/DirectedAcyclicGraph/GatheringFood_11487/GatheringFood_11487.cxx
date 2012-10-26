/*
  Problem: Gathering Food
  Link: http://uva.onlinejudge.org/external/114/11487.html
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: DP/DAG problem. Search DAG using bfs from A to B and then find total 
  number of paths to B. Similarly continue till the end. If you reach the end
  multiply the number of paths and display output.
*/

#include <cstdio>
#include <cstring>
#include <cassert>
#include <ctime>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits>
#include <queue>

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
#define MOD 20437

int N;
char forest[10][11];
char lastChar;
int rowStart, colStart;
int shortestPath;
int arrs[] = {-1, 1, 0, 0};
int sees[] = {0, 0, -1, 1};

void parseForest() {
	lastChar = 'A';
	REP(i, N) REP(j, N)
		if(isalpha(forest[i][j])) lastChar = max(forest[i][j], lastChar);
}

void findLocation(char searchChar) {
	REP(i, N) REP(j, N)
		if(forest[i][j] == searchChar) rowStart = i, colStart = j;
}

bool isValid(int row, int col) {
	return row < N && col < N && row >= 0 && col >= 0 && 
		forest[row][col] != '#' && 
		(forest[row][col] == '.' || 
		 forest[row][col] <= forest[rowStart][colStart]+1);
}

LL bfsShortestPath(char from, char to) {
	shortestPath = INF;
	
	VVL paths(N, VL(N, 0));
	paths[rowStart][colStart] = 1;
	VVI dist(N, VI(N, INF));
	dist[rowStart][colStart] = 0;
	queue<pair<int ,PII> > Q;
	Q.push(mp(0, mp(rowStart, colStart)));
	pair<int, PII> curNode;
	int curRow, curCol, curLength, r, c;
	while(!Q.empty() && Q.front().first < shortestPath) {
		curNode = Q.front(); Q.pop();
		curLength = curNode.first;
		curRow = curNode.second.first;
		curCol = curNode.second.second;
		//printf("(%d %d) %d %lld\n", curRow, curCol, curLength, paths[curRow][curCol]);
		for(int i = 0; i < 4; ++i) {
			r = curRow+arrs[i];
			c = curCol+sees[i];
			if(isValid(r, c)) 
				if(dist[r][c] == INF) {
					dist[r][c] = curLength+1;
					paths[r][c] += paths[curRow][curCol];
					Q.push(mp(curLength+1, mp(r, c)));
					if(forest[r][c] == to) 
						shortestPath = curLength + 1;
				}
				else if(dist[r][c] == curLength+1)
					paths[r][c] += paths[curRow][curCol];
		}
	}
	
	REP(i, N) REP(j, N) if(forest[i][j] == to) 
	{ rowStart = i, colStart = j; }

	return paths[rowStart][colStart];
}

void solveGatheringFood() {
	int test = 1;
	int nPaths;
	LL numOfDistinctPaths;
	char from;
	int sp;
	while(scanf("%d",&N) != EOF && N != 0) {
		REP(i, N) scanf("%s",forest[i]);

		// identify the last character.
		parseForest();
		findLocation('A');
		numOfDistinctPaths = 1;
		sp = 0;
		for(from = 'A'; from != lastChar; ++from) {

			nPaths = bfsShortestPath(from, from+1);
			sp += shortestPath;
			if(nPaths == 0) break;

			numOfDistinctPaths = (numOfDistinctPaths*nPaths)%MOD;
		}

		printf("Case %d: ", test++);
		if(from == lastChar)
			printf("%d %lld\n", sp, numOfDistinctPaths);
		else
			printf("Impossible\n");
	}
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	// solve something here
	solveGatheringFood();

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
