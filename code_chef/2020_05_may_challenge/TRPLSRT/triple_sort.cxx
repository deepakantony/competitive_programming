/*
  Problem: Template CPP main file.
  Link:
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution:
*/

#include <climits>
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
#include <tuple>

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
		int N, K; cin >> N >> K;
		VI pi(N+1,0); FOR(i, 1, N+1) cin >> pi[i];

		vector<tuple<int,int,int>> triples;
		vector<tuple<int,int>> doubles;
		int i = 1;
		while(i<=N) {
			//cout << "i: " << i << endl;
			//FOR(j, 1, N+1) cout << pi[j] << " ";
			//cout << endl;
			if(pi[i] == i)
				++i;
			else {
				int ai = i, bi = pi[ai], ci = pi[bi];
				if (ci == ai) {
					if (ai < bi) doubles.push_back(make_tuple(ai, bi));
					++i;
				}
				else {
					triples.push_back(make_tuple(ai, bi, ci));
					swap(pi[ai], pi[bi]);
					swap(pi[ai], pi[ci]);
					//pi[ai] = ci; pi[bi] = ai; pi[ci] = bi;
				}
			}
		}

		if(doubles.size()%2 == 0) {
			for(int i = 0; i < doubles.size(); i+=2) {
				int a,b,c,d;
				tie(a,b) = doubles[i];
				tie(c,d) = doubles[i+1];
				triples.push_back(make_tuple(a,b,c));
				triples.push_back(make_tuple(a,d,c));
			}

			if(triples.size() <= K) {
				cout << triples.size() << endl;
				REP(i, triples.size()) {
					int a, b, c;
					tie(a,b,c) = triples[i];
					cout << a << " " << b << " " << c << endl;
				}
			}
			else {
				cout << "-1" << endl;
			}
		}
		else {
			cout << "-1" << endl;
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
