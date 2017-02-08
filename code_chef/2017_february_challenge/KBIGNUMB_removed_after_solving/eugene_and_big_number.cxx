/*
  Problem: eugene and big number
  Link:
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: X = A * ( 1 + 10^di + 10^2di + ... + 10^(N-1)di ) where A is the number repeated N times, di is the number of digits in A.
  This is geometric sum which can be calculated recursively in logN time.
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

UL POW(UL b, UL e, UL M)
{
	b%=M;
	UL res = 1;
	while (e>0) {
		if (e%2==1) res = (res*b)%M;
		b = (b*b)%M;
		e /= 2;
	}
	return res;
//	b%=M;
//	if (e==0) return 1;
//	if (e==1) return b;
//	if (e==2) return (b*b)%M;
//
//	UL pow_2 = POW(b,e/2,M)%M;
//	UL even_part = (pow_2*pow_2)%M;
//	if (e%2 == 0) return even_part;
//	return (b*even_part)%M;
}

UL geo_sum_mod( UL a, UL r, UL N, UL M )
{
	if (N==0) return 0;
	if (N==1) return a%M;
	if (N==2) return ((a%M)+((a%M)*(r%M)))%M;

	// ORIGINAL
	if (N%2==0) return (((1+r%M)%M)*(geo_sum_mod(a%M, ((r%M)*(r%M))%M, N/2, M)%M))%M;
	return ( geo_sum_mod(a, r, N-1, M)%M + ((a%M)*POW(r,N-1,M))%M)%M;
}

UL geo_sum_mod( UL r, UL N, UL M )
{
	r %= M;
	if (N==0) return 0;
	if (N==1) return 1;
	if (N==2) return (1+r)%M;

	UL sum_half = geo_sum_mod(r*r, N/2, M);
	UL even_part = (((1+r)%M)*(sum_half))%M;
	if (N%2==0) return even_part;
	//else
	return (even_part+POW(r,N-1,M))%M;
}

UL num_digits( UL N)
{
	UL d = 0;
	while (N>0) {
		N/=10;
		++d;
	}
	return d;
}

void solve()
{
	int T; cin >> T;

	while (T--) {
		UL A,N,M; cin >> A >> N >> M;
		UL di = num_digits(A);
		UL r = POW(10, di, M);

		//cout << ((A%M) * geo_sum_mod(r,N,M))%M << " --> " << (geo_sum_mod(r,N,M))%M << "\n\t(A,N,M,di,r) (" << A << "," << N << "," << M <<","<< di <<","<< r<< ")" <<endl;
		cout << ((A%M) * geo_sum_mod(r,N,M))%M << endl;
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
