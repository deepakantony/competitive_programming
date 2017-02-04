/*
  Problem: Chef and triangles
  Link:
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: O(nlogn) for sorting; O(n) to count;
  Triangle with A[i] & A[i-1] is possible if the length (l) of new strand is A[i]-A[i-1] < l < A[i]+A[i+1]
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
	UL N,L,R; cin >> N >> L >> R;
	vector<UL> A(N,0); REP(i, N) cin >> A[i];
	sort(A.begin(), A.end());

	UL possible = 0;
	UL cur_lo = 0, cur_hi = 0;
	for (LL i = A.size()-1; i > 0; --i) {
		UL new_lo = A[i] - A[i-1] + 1;
		UL new_hi = A[i] + A[i-1];

		if (cur_lo == 0 || cur_hi == 0) {
			cur_lo = new_lo; cur_hi = new_hi;
		}
		else if ((new_hi-1) >= cur_lo)
			cur_lo = min(cur_lo, new_lo);
		else if (cur_lo <= R && (cur_hi-1) >= L) {
			possible += min(cur_hi, R+1) - max(cur_lo, L);
			cur_hi = new_hi;
			cur_lo = new_lo;
		}
	}

	if (cur_lo <= R && (cur_hi-1) >= L) {
		possible += min(cur_hi, R+1) - max(cur_lo, L);
	}

	cout << possible << endl;
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
