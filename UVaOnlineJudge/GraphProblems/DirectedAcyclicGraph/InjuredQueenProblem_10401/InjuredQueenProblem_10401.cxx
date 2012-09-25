/*
  Problem: Injured Queen Problem
  Link: http://uva.onlinejudge.org/external/104/10401.html
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: Implicit DAG, i.e. the direction of the every edge is either up or
  right if we start at "A1". Memoize the intermediate results to get the final
  answer.
*/

#include <cstdio>
#include <cstring>
#include <cassert>
#include <ctime>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits>
#include <string>

using namespace std;

typedef unsigned long long UL;
typedef long long LL;
typedef pair<int,int> PII;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<UL> VL;
typedef vector<VL> VVL;
typedef vector<PII> VPII;
typedef vector<VPII> VVPII;

#define REP(i, n) for(int i = 0; i < (n); ++i)
#define FOR(i, st, nd) for(int i = (st); i < (nd); ++i)
#define SET(a, val) memset(a, val, sizeof(a))
#define mp make_pair

#define INF numeric_limits<int>::max()

int convertInputToNumber(char inp){
	assert(inp != '?');
	int res;
	if(isalpha(inp)) res = inp-'A'+10;
	if(isdigit(inp)) res = inp-'0';
	return res;
}

// returns true if the initial arrangement given valid, given the problems 
// constraints; otherwise return false
bool initialArrangementIsPossible(char *inp, int boardSize) {
	REP(i, boardSize-1) 
		if(inp[i] != '?') {
			int inpi = convertInputToNumber(inp[i]);
			if(inpi > boardSize) return false;
			if(inp[i+1] != '?') {
				int inpi_1 = convertInputToNumber(inp[i+1]);
				if(inpi == inpi_1 || inpi == inpi_1+1 || inpi == inpi_1-1)
					return false; // not possible
			}
		}
	return true; // possible
}

VVI G;

// construct graph based on the input
void constructGraph(char *inp, int boardSize) {
	G.assign(boardSize*boardSize, VI());
	int start, end, toStart, toEnd;
	REP(row, boardSize) {
		if(inp[row] == '?') start = 0, end = boardSize;
		else {start = convertInputToNumber(inp[row])-1; end = start+1;}
		FOR(col, start, end) {
			int fromIndex = row*boardSize+col;

			FOR(toRow, row+1, boardSize) {
				if(inp[toRow] == '?') toStart = 0, toEnd = boardSize;
				else {toStart = convertInputToNumber(inp[toRow])-1; toEnd = toStart+1;}
				FOR(toCol, toStart, toEnd) {
					if(toRow == row+1 && toCol >= col-1 && toCol <= col+1)
						continue;
					G[fromIndex].push_back(toRow*boardSize+toCol);
				}
			}
		}
	}
}

VVL memo;

// DP for number of possible queen arrangements
UL numberOfArrangements(int curNode, int numberOfQueensLeft) {
	UL &res = memo[curNode][numberOfQueensLeft];
	if(res != -1)
		return res;
	if(numberOfQueensLeft == 1)
		return res = 1;
	res = 0;
	REP(i, G[curNode].size()) 
		res += numberOfArrangements(G[curNode][i], numberOfQueensLeft-1);
	return res;
}

// find the number of arrangements i.e. the final answer required
UL numberOfArrangements(int boardSize) {
	UL totalArrangements = 0;
	memo.assign(G.size(), VL(boardSize+1, -1));
	REP(i, G.size()) {
		totalArrangements += numberOfArrangements(i, boardSize);
	}
	return totalArrangements;
}

void solveInjuredQueenProblem() {
	char inp[20];
	int boardSize;
	while(scanf("%s", inp) != EOF) {
		boardSize = strlen(inp);
		if(initialArrangementIsPossible(inp, boardSize)) {
			constructGraph(inp, boardSize);
			UL res = numberOfArrangements(boardSize);
			printf("%llu\n", res);
		}
		else printf("0\n");
	}
}

void unitTests() {
	char inp[] = "??????";
	constructGraph(inp, 6);
	UL res1 = numberOfArrangements(6);
	VVI G1(G);
	VVL memo1(memo);
	constructGraph(inp, 6);
	UL res2 = numberOfArrangements(6);
	VVI G2(G);
	VVL memo2(memo);
	assert(G1.size() == G2.size());
	REP(i, G1.size()) {
		assert(G1[i].size() == G2[i].size());
		REP(j, G1[i].size())
			assert(G[i][j] == G2[i][j]);
	}
	assert(memo1.size() == memo2.size());
	REP(i, memo1.size()) {
		assert(memo1[i].size() == memo2[i].size());
		assert(memo1[i].size() == 7);
		REP(j, memo1[j].size()) {
			if(memo1[i][j] != memo2[i][j]) {
				printf("%d %d %llu %llu", i, j, memo1[i][j], memo2[i][j]);
				exit(-1);
			}
			
		}

	}
	printf("%llu %llu\n", res1, res2); fflush(stdout);
	assert(res1 == res2);
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
	freopen("Input_InjuredQueenProblem.txt", "r", stdin);
#endif 
	// solve something here
	solveInjuredQueenProblem();
	//unitTests();

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
