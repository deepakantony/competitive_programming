/*
  Problem: Fibonacci queries
  Link: https://www.codechef.com/APRIL16/problems/FIBQ
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: fibonacci num using matrix exponentiation & queries using fenwick tree
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
#define MOD_SUM(a,b) ((((a)%MOD)+((b)%MOD))%MOD)

struct Matrix2D {
	LL data[2][2];

	Matrix2D() { REP(i,2) REP(j,2) data[i][j] = 0; }

	Matrix2D operator*(const Matrix2D &other) const {
		Matrix2D res;
		REP(r,2) {
			REP(c, 2) {
				LL sum = 0;
				REP(rc, 2) {
					sum = MOD_SUM(sum, (data[r][rc] * other.data[rc][c])%MOD);
				}
				res.data[r][c] =sum;
			}
		}
		return res;
	}

	Matrix2D power(LL p) const {
		Matrix2D res;
		if( p == 0 ) { res.data[0][0] = res.data[1][1] = 1; }
		else if( p == 1 ) { res = *this; }
		else if( p%2 ) { res = *this * power(p-1); }
		else { res = power(p/2); res = res*res; }
		return res;
	}
};

LL fibonacci(LL n)
{
	Matrix2D m;
	m.data[0][0] = m.data[0][1] = m.data[1][0] = 1;
	m.data[1][1] = 0;

	return (m.power(n)).data[1][0];
}

void fibonacci_test()
{
	int T; cin >> T;
	while(T--)
	{
		int N; cin >> N; cout << "Fibonacci " << N << ":" << fibonacci(N) << endl;
	}
}

#define LSOne(x) ((x)&(-x))

class FenwickTree {
private:
	VL ft;
public:
	FenwickTree(int n) : ft(n+1,0) {}
	LL rsq(int b) { 
		LL sum = 0;
		for( ; b > 0; b-=LSOne(b)) sum = MOD_SUM(sum, ft[b]);
		return sum;
	}

	LL rsq(int a, int b) { if( a == 1 ) return rsq(b); else return MOD_SUM( rsq(b), -rsq(a-1)); }

	void adjust(int k, LL v) {
		for( ; k < ft.size(); k += LSOne(k) ) ft[k] += v;
	}
};

void solve()
{
	int N,M; cin >> N >> M;
	FenwickTree tree(N);

	REP(i, N)
	{
		int Ai; cin >> Ai;
		tree.adjust(i+1, Ai);
	}

	while(M--)
	{
		char Q; cin >> Q;
		int A,B; cin >> A >> B;
		
		if( Q=='C' ) tree.adjust(A,B);
		else cout << 
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
