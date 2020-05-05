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

typedef vector<VVPII> VVVPII;

// brute force method
int count_intersecting_bf(const VI &A, int N, int x1, int x2, int y) {
	int count = 0;
	for(int p = x1; p < x2; ++p) {
		int low = min(A[p-1], A[p]);
		int high = max(A[p-1], A[p]);
		if(low <= y && y <= high)
			++count;
	}
	return count;
}

void solve() {
	int T; cin >> T;
	while(T--) {
		int N, Q; cin >> N >> Q;
		VI A(N, 0); REP(i, N) cin >> A[i];

		REP(i, Q) {
			int x1, x2, y; cin >> x1 >> x2 >> y;

			cout << count_intersecting_bf(A, N, x1, x2, y) << endl;
		}
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
