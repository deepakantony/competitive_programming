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

template<typename IT, typename T>
IT find_first_not_of(IT begin, IT end, const T &val) 
{
  return find_if(begin, end, [val](const T &list_val){ return val!=list_val; });
}

void solve()
{
  int T; cin >> T;
  while(T--) {
    int N; cin >> N;
    VI A(N,0);
    REP(i,N) cin >> A[i];
    sort(A.begin(), A.end());

    int num_of_conversions = 0;

    for(auto it = A.begin(); it != A.end();) {
      auto new_it = find_first_not_of(it, A.end(), *it);
      num_of_conversions += distance(it+1, new_it);

      it = new_it;
    }

    cout << num_of_conversions << "\n";
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
