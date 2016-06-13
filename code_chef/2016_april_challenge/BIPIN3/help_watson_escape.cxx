/*
  Problem: Help watson escape
  Link: https://www.codechef.com/APRIL16/problems/BIPIN3
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: counting
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
#define MOD (1000000007)

LL mod_exp(LL x, LL y, LL mod)
{
	if( y == 0 )
		return 1;
	if( y == 1 )
		return x;
	if( y%2 ) // odd
		return (mod_exp(x,y-1,mod)*x)%mod;
	// even
	LL res_y2 = mod_exp(x,y/2,mod);
	return (res_y2*res_y2)%mod;
}

void solve()
{
	int T; cin >> T;

	while(T--)
	{
		LL N,K; cin >> N >> K; //cout << N << " " << K << " -> ";
		
		LL ans = (K*mod_exp(K-1,N-1,MOD))%MOD;

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
