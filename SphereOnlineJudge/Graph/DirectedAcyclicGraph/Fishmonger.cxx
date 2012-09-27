/*
  Problem: Fishmonger
  Link: http://www.spoj.pl/problems/FISHER/
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: build a DAG. Apply DP with an additional parameter.
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

#define INF 1000000000

int N, timeLimit;
int travelTime[55][55], toll[55][55];
PII memo[55][1010];

PII getTollAndTime(int curCity, int timeLeft) {

	if(timeLeft < 0) return PII(INF, INF);
	if(memo[curCity][timeLeft] != PII(-1,-1)) return memo[curCity][timeLeft];
	if(curCity == (N-1)) return memo[curCity][timeLeft] = PII(0, 0);
	PII res(INF, INF);
	REP(v, N) if(v != curCity) {
		PII nextCity = getTollAndTime(v, timeLeft-travelTime[curCity][v]);
		if(nextCity.first + toll[curCity][v] < res.first) {
			res.first = nextCity.first + toll[curCity][v];
			res.second = nextCity.second + travelTime[curCity][v];
		}
	}

	return memo[curCity][timeLeft] = res;
}

void solveFishmonger() {
	while(scanf("%d %d", &N, &timeLimit) != EOF && N != 0) {
		REP(i, N) REP(j, N) scanf("%d", &travelTime[i][j]);
		REP(i, N) REP(j, N) scanf("%d", &toll[i][j]);

		REP(i, N) REP(t, timeLimit+1) memo[i][t] = PII(-1, -1);
		
		PII res = getTollAndTime(0, timeLimit);
		printf("%d %d\n", res.first, res.second);
	}
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	// solve something here
	solveFishmonger();

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
