/*
  Problem: Bear and xtra number.
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

void solve()
{
	int T; cin >> T;

	while(T--) {
		int N; cin >> N;
		VI vec(N,0); REP(i,N) cin >> vec[i];
		sort(vec.begin(), vec.end());
		if (vec[0] < vec[1]-1) // is it the min
			cout << vec[0] << endl; 
		else if (vec[vec.size()-1] > vec[vec.size()-2]+1) // is it the max
			cout << vec[vec.size()-1] << endl;
		else {
			map<int,int> mp;
			for( auto x : vec ) {
				mp[x] += 1;
				if (mp[x] > 1) {
					cout << x << endl;
					break;
				}
			}
		}
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
