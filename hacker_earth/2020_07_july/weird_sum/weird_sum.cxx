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
LL N, K, M;
VVL memo;
LL max_sum(VL &A, LL i, LL k){
  if(memo[i][k] != numeric_limits<LL>::min()) return memo[i][k];
  if(k==1) {
    memo[i][k] = (A[i]*(K%M));
    if(i+1 < N) {
      memo[i][k] = max(memo[i][k], max_sum(A, i+1, k));
    }
  }

  else if((N-i)==k) {
    LL sum = 0;
    REP(j, k){
      sum += (A[i+j]*((K-k+j+1)%M));
    }
    memo[i][k] = sum;
  }
  else {
    LL with_i = A[i]*((K-k+1)%M) + max_sum(A, i+1, k-1);
    LL withou_i = max_sum(A, i+1, k);
    memo[i][k] = max(with_i, withou_i);
  }
  //cout << "i: " << i << " k: " << k;
  //cout << " memo[i][k]: " << memo[i][k] << endl;
  return memo[i][k];
}
/*
int max_sum_FP(VI &A) {

}
*/
void solve() {
    cin >> N >> K >> M;
    memo.assign(N+1, VL(K+1, numeric_limits<LL>::min()));
    VL A(N, 0); REP(i, N) cin >> A[i];
    if(K==0) cout << 0 << endl;
    else
      cout << max_sum(A, 0, K) << endl;
    /*
    REP(i, N) { REP(j, K+1) {
      cout << "\t" << memo[i][j];
    }
    cout << endl;
    }
    */
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
