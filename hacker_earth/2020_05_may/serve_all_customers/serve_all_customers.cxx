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
#include <queue>

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

struct Cstmr {
	int i, A, B, C;
};
bool pqcmp(const Cstmr &a, const Cstmr &b) {
	if (b.A < a.A) return true;
	if ((a.A == b.A) && (b.B < a.B)) return true;
	if ((a.A == b.A) && (a.B == b.B) && (b.C < a.C)) return true;
	return false;
}

void solve() {
	UL N, K; cin >> N >> K;
	vector<Cstmr> cstmr(N, Cstmr());
	REP(i, N) cin >> cstmr[i].A;
	REP(i, N) cin >> cstmr[i].B;
	REP(i, N) cin >> cstmr[i].C;
	REP(i, N) cstmr[i].i = i;
	//REP(i, N) cout << cstmr[i].i << " : " << cstmr[i].A << " : " << cstmr[i].B << " : " << cstmr[i].C <<endl;
	priority_queue<Cstmr, vector<Cstmr>, decltype(&pqcmp)> pq(pqcmp);
	REP(i, N) pq.push(cstmr[i]);

	priority_queue<Cstmr, vector<Cstmr>, decltype(&pqcmp)> cooking(pqcmp);
	VI results(N, 0);
	int t = 0;
	while(!pq.empty()) {
		while (!cooking.empty() && cooking.top().A <= pq.top().A) cooking.pop();

		auto c = pq.top(); pq.pop();
		if (cooking.size() >= K) {c.A = cooking.top().A; cooking.pop();}
		results[c.i] = c.A;
		c.A += c.B;
		cooking.push(c);
	}
	REP(i, N) cout << results[i] << " ";
	cout << endl;
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
