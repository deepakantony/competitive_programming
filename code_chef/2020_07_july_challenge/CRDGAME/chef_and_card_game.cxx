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

int sum_o_dgts(int n) {
    int res = 0;
    while(n>0) {
        res += (n%10);
        n /= 10;
    }
    return res;
}

void solve() {
    int T; cin >> T;
    while(T--) {
        int N; cin >> N;
        int sA = 0, sB = 0;
        while(N--) {
            int A,B; cin >> A >> B;
            int sodA = sum_o_dgts(A);
            int sodB = sum_o_dgts(B);
            if(sodA>=sodB) ++sA;
            if(sodB>=sodA) ++sB;
        }
        if(sA==sB) cout << "2 " << sA << endl;
        else if(sA>sB) cout << "0 " << sA << endl;
        else cout << "1 " << sB << endl;
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
