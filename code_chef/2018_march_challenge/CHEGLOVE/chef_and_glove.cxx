/*
  Problem: Template CPP main file.
  Link: https://www.codechef.com/MARCH18B/problems/CHEGLOVE
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: looks simple!
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

    VI fingers(N,0); REP(i, N) cin >> fingers[i];
    VI sheaths(N,0); REP(i, N) cin >> sheaths[i];

    bool front = true, back = true;
    REP(i,N) if(sheaths[i] < fingers[i]) front = false;
    REP(i,N) if(sheaths[i] < fingers[N-1-i]) back = false;
    if(front && back)
      cout << "both\n";
    else if (front)
      cout << "front\n";
    else if (back)
      cout << "back\n";
    else cout << "none\n";
  }
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	solve();

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
