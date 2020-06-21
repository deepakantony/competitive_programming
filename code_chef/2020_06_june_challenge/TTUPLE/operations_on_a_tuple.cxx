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

int rec_solve(int p, int q, int r, int a, int b, int c, int depth) {
    if(p==a&&q==b&&r==c) return depth;
    if(depth == 2) return 3;
    set<int> add{a-p,b-q,c-r};
    set<int> mult{0};
    if(p!=0)mult.insert(a/p);
    if(q!=0)mult.insert(b/q);
    if(r!=0)mult.insert(c/r);
    if(p!=q)mult.insert((a-b)/(p-q));
    if(p!=r)mult.insert((a-c)/(p-r));
    if(q!=r)mult.insert((b-c)/(q-r));
    int res = 3;
    FOR(i, 1, 8) {
        for(auto v: add) {
            int new_p = (i&1) ? p+v : p;
            int new_q = (i&2) ? q+v : q;
            int new_r = (i&4) ? r+v : r;
            res = min(res, rec_solve(new_p, new_q, new_r, a, b, c, depth+1));
        }
        for(auto v: mult) {
            int new_p = (i&1) ? p*v : p;
            int new_q = (i&2) ? q*v : q;
            int new_r = (i&4) ? r*v : r;
            res = min(res, rec_solve(new_p, new_q, new_r, a, b, c, depth+1));
        }
    }
    return res;
}

void solve() {
    int T; cin >> T;
    while(T--) {
        int p,q,r; cin >> p >> q >> r;
        int a,b,c; cin >> a >> b >> c;

        cout << rec_solve(p,q,r,a,b,c,0) << endl;
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
