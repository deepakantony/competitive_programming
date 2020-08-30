/*
  Problem: Template CPP main file.
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
#include <climits>

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

int memo[1001];
int N, K;
int F[1000];

int dp(int i) {
	if(memo[i] == -1) {
		VI fbin(101, 0);
		fbin[F[i]] = 1;
		int best_cost = INT_MAX;
		int cost_fbin = K;
		for (int j = i+1; j < N; ++j) {
			best_cost = min(best_cost, cost_fbin + dp(j));

			if(fbin[F[j]]==1) cost_fbin += 2;
			else if(fbin[F[j]]>1) cost_fbin +=1;
			fbin[F[j]] += 1;
		}
		best_cost = min(best_cost, cost_fbin); // include the last person
		memo[i] = best_cost;
	}
	return memo[i];
}

void solve() {
	int T; cin >> T;
	while(T--) {
		cin >> N >> K;
		REP(i, N) cin >> F[i];
		SET(memo, -1);
		cout << dp(0) << endl;
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
