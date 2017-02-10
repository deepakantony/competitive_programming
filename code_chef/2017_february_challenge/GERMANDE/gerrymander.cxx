/*
  Problem: Gerrymander
  Link:
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: Precalculate a SUM array where SUM[i] = sum(A,0,i) --> O(N)
  A SUM between i & j indicates number of 1 voters.
  We can just query o2 times every o1 district as to who would win. This is O(1) for every query and there are N queries at the max.
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

class SUMCirc {
public:
	SUMCirc(const VI &A) : sum(A){
		for (int i = 1; i < sum.size(); ++i)
			sum[i] += sum[i-1];
	}
	SUMCirc(int *A, int size) : sum(A, A+size){
		for (int i = 1; i < sum.size(); ++i)
			sum[i] += sum[i-1];
	}

	int Query(int i, int blocksize) const {
		//if (blocksize > sum.size() || i >= sum.size()) return 0;
		//if (blocksize == 0) return 0;
		if (i==0) return sum[blocksize-1];

		if (i+blocksize > sum.size())
			return sum[sum.size()-1]-sum[i-1]+sum[i+blocksize-sum.size()-1];
		return sum[i+blocksize-1]-sum[i-1];
	}
private:
	VI sum;
};

void solve()
{
	int T; cin >> T;
	while (T--) {
		int o1,o2; cin >> o1 >> o2;
		int N = o1*o2;
		VI votes(N,0);
		for(int i = 0; i < N; ++i) cin >> votes[i];
		SUMCirc sumcirc(votes);

		int pres_thresh = o1>>1;
		int state_thresh = o2>>1;
		int state_won = 0;
		//cout << "pres_thresh: " << pres_thresh << ", state_thresh: " << state_thresh << endl;
		for(int i = 0; i < o2; ++i) {
			//cout << "i: "<< i << endl;
			state_won = 0;
			for( int j = i; j < N; j+=o2 ) {
				int sum_j = sumcirc.Query(j,o2);
				//cout << "j: " << j << ", Sum_j : " << sum_j << endl;
				state_won += (sum_j > state_thresh) ? 1 : 0;
				if (state_won > pres_thresh) break;
			}
			if (state_won > pres_thresh) break;
		}
		cout << ((state_won > pres_thresh) ? "1" : "0") << endl;
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
