/*
  Problem: Cycle race
  Link:
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: similar to nims game with history
*/

#include <cstdio>
#include <cmath>
#include <cstring>
#include <cassert>
#include <ctime>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <map>

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
#define EPS (1e-9)
#define FLT_EQ(x,y) ((fabs((x)-(y))) < EPS)

void solve()
{
	int T; cin >> T;
	VI jelly_wins;

	while(T--) {
		int N; cin >> N;

		while(jelly_wins.size() < N) {
			int cur_N = jelly_wins.size() + 1;
			int cur_jelly_wins = 0;
			if (cur_N == 1 || cur_N == 2 || cur_N == 4)
				cur_jelly_wins = 1;
			else if (cur_N == 3)
				cur_jelly_wins = 0;
			else if (!jelly_wins[cur_N-4-1] || !jelly_wins[cur_N-2-1] || !jelly_wins[cur_N-1-1])
				cur_jelly_wins = 1;
			jelly_wins.push_back(cur_jelly_wins);
		}

		cout << (jelly_wins[N-1] == 0 ? "JACK" : "JELLY") << endl;
	}
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	// solve something here
	solve();

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
