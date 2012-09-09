/*
  Problem: Three is Crowd
  Link: http://www.codechef.com/SEP12/problems/CROWD
  Author: deebee
  Solution: Forms the series 1, 3, 8, 20, 47, ... This is given by 2^N - 
  tribonacci(N+4)
*/

#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
#include <ctime>

using namespace std;

#define REP(i, n) for(int i = 0; i < (n); ++i)
#define FOR(i, st, nd) for(int i = (st); i < (nd); ++i)

typedef long long LL;
typedef vector<LL> VL;
typedef vector<VL> VVL;

#define MOD 1000000007

inline LL modme(LL n) {
	if(n < 0) return MOD+n;
	return n%MOD;
}

class SquareMatrix {
public:
	SquareMatrix() : size(3) {memset(mat, 0, sizeof mat);}

	SquareMatrix multiply(const SquareMatrix &other) const {
		assert(size == other.size);
		SquareMatrix res;
		REP(x, size) REP(y, size) {
			REP(z, size)
				res.mat[x][y] = (res.mat[x][y] + 
								 (mat[x][z]*other.mat[z][y])%MOD)%MOD;
			//res.mat[x][y] %= MOD;
		}
		return res;
	}

	SquareMatrix exponentiate(LL exp) {
		SquareMatrix base = SquareMatrix(*this);
		SquareMatrix res;
		REP(x, size) res.mat[x][x] = 1;
		while(exp>0) {
			if(exp%2) res = res.multiply(base);
			exp>>=1;
			base = base.multiply(base);
		}
		
		return res;
	}

	void print() const {
		REP(x, size) { REP(y, size) printf("%lld\t", mat[x][y]); printf("\n"); }
	}
	int size;
	LL mat[3][3];
};

class TribonacciMatrix : public SquareMatrix {
public:
	TribonacciMatrix() : SquareMatrix() {
		mat[0][0] = mat[0][1] = mat[0][2] = 1;
		mat[1][0] = mat[2][1] = 1;
	}

	LL tribonacciNumber(LL n) {
		if(n<3) return 0;
		if(n==3) return 1;
		return this->exponentiate(n-2).mat[0][2];
	}
};

void tribonacciSeries(LL n) {
    TribonacciMatrix tribonacci;
	FOR(i, 1, n+1) printf("%lld\n", tribonacci.tribonacciNumber(i));
}

LL modularExponentiation(LL base, LL exp) {
	LL res = 1;
	while(exp > 0) {
		if(exp%2) res = (res*base)%MOD;
		exp>>=1;
		base = (base*base)%MOD;
	}
	return res;
}

void contiguousSeries(LL n) {
    TribonacciMatrix tribonacci;
	FOR(i, 1, n+1) printf("%lld\n", 
						  modme(modularExponentiation(2, i) - 
								tribonacci.tribonacciNumber(i+4)));
}

void solveCROWD() {
	LL T, N; scanf("%lld", &T);
	TribonacciMatrix tribonacci;
	while(T--) {
		scanf("%lld", &N);
		printf("%lld\n", 
			   modme(modularExponentiation(2, N) - 
					 tribonacci.tribonacciNumber(N+4)));
	}
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif
	solveCROWD();
#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken: %.5f seconds\n", 
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}

