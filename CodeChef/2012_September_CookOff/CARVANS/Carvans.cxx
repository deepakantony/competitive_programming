/*
  Problem: Carvans
  Link: http://www.codechef.com/COOK26/problems/CARVANS
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: find if each vehicle has speed slower than the previous car
*/

#include <cstdio>
#include <cstring>
#include <cassert>
#include <ctime>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits>

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

void solveCarvans() {
	int T; scanf("%d", &T);
	int nCars; int speed[10000];
	while(T--) {
		scanf("%d", &nCars);

		assert(nCars >= 1);
		scanf("%d", &speed[0]);
		int res = 1;
		FOR(i, 1, nCars) {
			scanf("%d", &speed[i]);
			if(speed[i] > speed[i-1])
				speed[i] = speed[i-1];
			else ++res;
		}
		printf("%d\n", res);
	}
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	// solve something here
	solveCarvans();

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
