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

void solve() {
	int T; cin >> T;
	while(T--) {
		string S, P; cin >> S >> P;

		int sbin[26]; SET(sbin, 0);
		REP(i, S.size()) sbin[S[i]-'a'] += 1;
		REP(i, P.size()) sbin[P[i]-'a'] -= 1;
		string res;
		int i = 0;
		for(;i<26 && P[0] > char('a'+i); ++i)
			for(int j = 0; j < sbin[i]; j++)
				res += char('a'+i);

		int pi = 0;
		for(; pi < P.size() && P[pi]==char('a'+i); pi++)
			res += P[pi];
		if(pi < P.size() && P[pi] > char('a'+i)) {
			for(int j = 0; i < 26 && j < sbin[i]; ++j)
				res += char('a'+i);
			++i;
		}
		for(; pi < P.size(); pi++) {
			res += P[pi];
		}
		for(; i < 26; ++i) {
			for(int j = 0; j < sbin[i]; j++)
				res += char('a'+i);
		}
		cout << res << endl;
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
