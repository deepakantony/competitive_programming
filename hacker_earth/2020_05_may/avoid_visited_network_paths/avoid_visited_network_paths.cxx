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
#include <set>

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

#define M10E9 1000000007
#define X 212072634227239451

struct Node {
	LL p;
	set<LL> divisors;
	Node(LL op = 1) : p(op), divisors(){}
	void update_for_safety(){
		p = (divisors.find(X) != divisors.end()) ? 0 : p;
	}
	void update_for_A(LL A, Node const &above, Node const &left) {
		p = (above.p + left.p)%M10E9;
		set<LL> all_divisors(above.divisors);
		for (auto d: left.divisors) all_divisors.insert(d);

		if(A%11449==0) {
			if(above.divisors.empty() || left.divisors.empty()) {
				divisors.insert(11449);
			}
			for(auto d: all_divisors){
				if(d%11449 == 0) divisors.insert(d);
				else if (d%107 == 0) divisors.insert(d*107);
				else divisors.insert(d*11449);
			}
		}
		else if (A%107==0) {
			if(above.divisors.empty() || left.divisors.empty()) {
				divisors.insert(107);
			}
			for(auto d: all_divisors){
				if(d%11449 == 0) divisors.insert(d);
				else divisors.insert(d*107);
			}
		}

		if(A%1852321==0) {
			if(above.divisors.empty() || left.divisors.empty()) {
				divisors.insert(1852321);
			}
			for(auto d: all_divisors){
				if(d%1852321 == 0) divisors.insert(d);
				else if (d%1361 == 0) divisors.insert(d*1361);
				else divisors.insert(d*1852321);
			}
		}
		else if (A%1361==0) {
			if(above.divisors.empty() || left.divisors.empty()) {
				divisors.insert(1361);
			}
			for(auto d: all_divisors){
				if(d%1852321 == 0) divisors.insert(d);
				else divisors.insert(d*1361);
			}
		}

		if (A%10000019==0) {
			if(above.divisors.empty() || left.divisors.empty()) {
				divisors.insert(10000019);
			}
			for(auto d: all_divisors){
				if(d%10000019 == 0) divisors.insert(d);
				else divisors.insert(d*10000019);
			}
		}
	}
};

void solve() {
	int n, m; cin >> n >> m;
	VVL A(n, VL(m, 0));
	REP(i, n) REP(j, m) cin >> A[i][j];

	vector<vector<Node>> matrix(n, vector<Node>(m, Node()));
	matrix[0][0].p = 1;

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
