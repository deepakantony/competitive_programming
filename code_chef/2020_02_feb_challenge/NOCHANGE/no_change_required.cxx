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

void check_change(int N, int P, const VI &D) {
	REP(i, N) {
		if(P%D[i] != 0) {
			cout << "YES";
			REP(j, N) cout << " " << ((i==j) ? 1+(P/D[i]) : 0);
			cout << endl;
			return;
		}
	}

	REP(i, N) {
		FOR(j, i+1, N) {
			int minij = min(D[i],D[j]);
			int maxij = max(D[i],D[j]);
			if( maxij%minij != 0) {
				cout << "YES";
				REP(k, N) {
					cout << " ";
					if(k==i || k == j) {
						cout << ((minij==D[k]) ? ((P/D[k])-(maxij/minij)): 1);
					}
					else cout << "0";
				}

				cout << endl;
				return;
			}
		}
	}

	cout << "NO" << endl;
}

void solve() {
	int T; cin >> T;
	while(T--) {
		int N, P; cin >> N >> P;
		VI D(N, 0);
		REP(i, N) cin >> D[i];

		check_change(N, P, D);
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