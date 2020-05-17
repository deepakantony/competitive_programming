/*
  Problem: Template CPP main file.
  Link:
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution:
*/

#include <climits>
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
#include <tuple>

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

UL f(UL X, UL Y, UL Z) {
	return (X&Z)*(Y&Z);
}

UL solve_brute(UL X, UL Y, UL L, UL R) {
	UL Z = L;
	UL max_sofar = f(X,Y,Z);
	for(UL i = L+1; i < R+1; ++i) {
		UL prod = f(X, Y, i);
		if (prod > max_sofar) {
			max_sofar = prod;
			Z = i;
		}
	}
	return Z;
}

UL solve_1(UL X, UL Y, UL L, UL R) {
	UL Z = (X==0 || Y==0) ? 0 : X|Y;
	return Z;
}

UL solve_2(UL X, UL Y, UL L, UL R) {
	if (X==0 || Y==0) return 0;
	const UL bestZ = X|Y;
	const UL bits = sizeof(UL)*8;
	UL i = 0;
	UL Z = 0;
	UL potF = 0;
	UL potZ = 0;
	while(i < bits) {
		const UL mask = (UL(1)<<(bits-i-1));
		const UL mask_Z = mask | Z;
		cout << "i: " << i << " mask: " << mask << " mask_Z: " << mask_Z << " R: "<< R << " bestZ: " << bestZ <<  " Z: " << Z << endl;
		if(mask_Z <= R) {
			if((mask_Z&bestZ) == Z) {
				// This bit is not needed. And it is less than R so any number less than mask should be fine.
				UL cur_potZ = ((mask-1) & bestZ) | Z;
				potZ = (potF > f(X,Y,cur_potZ)) ? potZ : cur_potZ;
				Z = ((potZ&X) == 0 || (potZ&Y) == 0) ? 0 : potZ;
				break;
			}
			else if((mask&X) && (mask&Y)) {
				// used in both X & Y
				Z = mask_Z;
			}
			else
				potZ = (potF > )
				if((mask_Z&X))
				bestF = ((mask-1)) &
				Z = mask_Z;
			}
		}
		i++;
	}
	return Z;
}


UL solve_perf(UL X, UL Y, UL L, UL R) {
	UL Z = L;
	UL max_sofar = f(X,Y,Z);
	for(UL i = L; i < R+1; ++i) {
		UL prod = (X&i)*(Y&i);
		if (prod > max_sofar) {
			max_sofar = prod;
			Z = i;
		}
	}
	return Z;
}

void solve() {
	int T; cin >> T;
	while(T--) {
		UL X, Y, L, R; cin >> X >> Y >> L >> R;
		cout << solve_2(X, Y, L, R) << endl;
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
