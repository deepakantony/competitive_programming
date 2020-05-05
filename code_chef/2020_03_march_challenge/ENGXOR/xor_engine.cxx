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

int bitset_table256[256];
void init_bitset_table256() {
	bitset_table256[0] = 0;
	REP(i, 256) bitset_table256[i] = (i & 0x1) + bitset_table256[i/2];
}
int count_bit_set(int n) {
	return (bitset_table256[n & 0xFF] + bitset_table256[(n>>8) & 0xFF] +
		bitset_table256[(n>>16) & 0xFF] + bitset_table256[(n>>24) & 0xFF]);
}

int count_bit_set_logn(int n) {
	int count = 0;
	while(n) {
		count += (n&0x1);
		n >>= 1;
	}
	return count;
}

void solve() {
	init_bitset_table256();
	int T; scanf("%d", &T);
	int A[100002];
	while(T--) {
		int N, Q; scanf("%d%d", &N, &Q);
		REP(i, N) scanf("%d", &A[i]);
		int even = 0, odd = 0;
		REP(i, N) {
			int count = count_bit_set(A[i]);
			if (count%2 == 0) ++even;
			else ++odd;
		}
		REP(i, Q) {
			int P; scanf("%d", &P);
			int count = count_bit_set(P);
			if(count%2 == 0) printf( "%d %d\n", even, odd);
			else printf( "%d %d\n", odd, even);
		}
	}
}

int main(int argc, char *argv[]) {
	 ios_base::sync_with_stdio(false);
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
