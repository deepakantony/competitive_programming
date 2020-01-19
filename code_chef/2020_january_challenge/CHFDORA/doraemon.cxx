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

void read_matrix(VVI &M){
	for(VI &row : M)
		for(int &val : row)
			cin >> val;
}

int num_palindromic_pairs(const VVI &M, int r, int c, int R, int C) {
	int res_r = 0, res_c = 0;
	int lim_c = min(c, C-1-c);
	int lim_r = min(r, R-1-r);

	// Num of subrow palindromic
	for(int i = 1; i <= lim_c && M[r][c-i] == M[r][c+i]; ++i)
		++res_r;
	// Now subcolumn
	for(int i = 1; i <= lim_r && M[r-i][c] == M[r+i][c]; ++i)
		++res_c;

	return min(res_r, res_c);
}

void solve() {
	int T; cin >> T;
	while(T--) {
		int R, C; cin >> R >> C;
		VVI M(R, VI(C, 0));
		read_matrix(M);
		int pairs = R*C; // all individual entries
		for(int r = 1; r < R-1; ++r)
			for(int c = 1; c < C-1; ++c)
				pairs += num_palindromic_pairs(M, r, c, R, C);
		cout << pairs << endl;
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
