/*
  Problem: bandwidth of a matrix
  Link:
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: 
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

void solve() {
	int T; cin >> T;
	while (T--) {
		int N; cin >> N;
		int ones = 0;
		int zeros = 0;
		REP(i,N) REP(j,N) {
			int val; cin >> val;
			if (val == 1) ones++;
			else zeros++;
		}

		int bandwidth = 0;
		ones -= N;
		int cur_diag = N-1;
		while (ones > 0 && bandwidth < N && cur_diag > 0) {
			++bandwidth;
			if (ones > 2*cur_diag)
				ones -= (2*cur_diag);
			else ones = 0;
			cur_diag--;
		}

		cout << bandwidth << endl;
	}
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	solve();

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
