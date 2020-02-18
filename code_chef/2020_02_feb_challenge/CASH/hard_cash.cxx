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
#include <iterator>

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
	while(T--) {
		LL N, K; cin >> N >> K;
		VL A(N, 0);
		REP(i, N) cin >> A[i];

		VL ADD(N, 0);
		ADD[N-1] = (K-(A[N-1]%K))%K;
		for(int i = N-2; i >= 0; --i)
			ADD[i] = ADD[i+1] + ((K-(A[i]%K))%K);

		LL RES = (ADD[0]==0) ? 0 : numeric_limits<LL>::max();
		LL mandatory_rem = 0;
		LL K_multiples_avail = 0;
		REP(i, N-1) {
			const LL rem = A[i] % K;
			mandatory_rem += rem;
			K_multiples_avail += (A[i]-rem);

			// What is the residual coins when spliting C at i.
			LL res_coins = 0;
			LL coins_needed = ADD[i+1];
			if(mandatory_rem >= coins_needed)
				res_coins = (mandatory_rem-coins_needed);
			else {
				coins_needed -= mandatory_rem;
				if(K_multiples_avail >= coins_needed)
					res_coins = (K_multiples_avail-coins_needed)%K;
				else
					res_coins = numeric_limits<LL>::max();
			}

			RES = min(RES, res_coins);
		}
		RES = min(RES, mandatory_rem+(A[N-1]%K));
		cout << RES << endl;
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
