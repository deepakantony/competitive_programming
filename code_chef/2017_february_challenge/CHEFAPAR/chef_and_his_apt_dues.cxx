/*
  Problem: Chef and his apartment dues
  Link: CHEFAPAR
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: simple!
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

	while(T--) {
		int N; cin >> N;
		VI A(N,0);
		REP(i,N) cin >> A[i];

		int start_of_fine = 0;
		for (int val : A)
			if (val == 0) break;
			else ++start_of_fine;

		int num_of_zeros = count(A.begin(), A.end(), 0);

		cout << num_of_zeros * 1000 + (N-start_of_fine)*100 << endl;
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
