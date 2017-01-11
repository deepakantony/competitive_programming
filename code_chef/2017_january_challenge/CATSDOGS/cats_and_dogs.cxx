/*
  Problem: Cats and dogs
  Link: https://www.codechef.com/JAN17/problems/CATSDOGS
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: simple analysis.
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

void solve_cats_and_dogs()
{
	int T; cin >> T;
	while(T--) {
		int C,D,L;
		cin >> C >> D >> L;

		int N = L/4;

#ifndef ONLINE_JUDGE
		cout << C << " " << D << " " << L << ": ";
#endif

		if ( L%4 == 0 && // ensure we counted 4 legs per animal
			 N <= (C+D) && // total num of animal should be less than count of cats & dogs
			 N >= D && // min is num of dogs
			 (C+D-N) <= 2*D // number of cats on top of dogs should be less than twice the number of dogs
			)
			cout << "yes\n";
		else
			cout << "no\n";
	}
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	// solve something here
	solve_cats_and_dogs();

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
