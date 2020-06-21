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

void solve() {
    int T; cin >> T;
    while(T--) {
        int N; cin >> N;
        map<int,int> coins = {{5,0}, {10,0}, {15,0}};
        string ans = "YES";
        VI A(N, 0);
        REP(i, N) cin >> A[i];
        for(auto a: A) {
            if(a==10) {
                if(coins[5]>=1)coins[5] -= 1;
                else {
                    ans = "NO";
                    break;
                }
            }
            else if(a==15) {
                if (coins[10] >= 1) coins[10] -= 1;
                else if (coins[5] >= 2) coins[5] -= 2;
                else {
                    ans = "NO";
                    break;
                }
            }
            coins[a] += 1;
        }
        cout << ans << endl;
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
