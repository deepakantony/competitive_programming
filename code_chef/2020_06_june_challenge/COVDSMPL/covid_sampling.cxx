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

void query(VVI &A, int N, int P) {
    int count = 0;
    cout << "1 1 1 " << N << " " << N << endl;
    int tot; cin >> tot;
    //int tot = (P*N*N)/100;
    REP(i, N) REP(j, N) {
        cout << 1 << " " << i + 1 << " " << j + 1 << " " << i + 1 << " " << j + 1 << endl;
        cin >> A[i][j];
        if(A[i][j]) ++count;
        if(count>=tot) return;
    }
}

void solve() {
    int T; cin >> T;
    while(T--) {
        int N, P; cin >> N >> P;
        VVI A(N, VI(N, 0));
        query(A, N, P);
        cout << 2 << endl;
        REP(i, N) {
            REP(j, N) cout << A[i][j] << " ";
            cout << endl;
        }
        int X;
        cin >> X;
        assert(X!=-1);
        if(X==-1) return;
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
