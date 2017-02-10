/*
  Problem: Most frequent element
  Link:
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: For every element create arrays - start & end where start[i],end[i] indicates where the A[i] starts and ends.
  To find element repeated k times or more which is atleast half the range size will always span the center of the range. So we just check the start and end of the middle element in that range.
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
	int N, M; cin >> N >> M;
	VL A(N,0); REP(i,N) cin >> A[i];
	VI start(N,0), end(N,N-1);

	for (int i = 1; i < N; ++i)
		start[i] = (A[i] == A[i-1]) ? start[i-1] : i;

	for (int i = N-2; i >= 0; --i)
		end[i] = (A[i] == A[i+1]) ? end[i+1] : i;
	
	while(M--) {
		int L, R, k; cin >> L >> R >> k;
		int mid = L-1 + (R+1-L)/2;
		int s = max(L-1,start[mid]);
		int e = min(R-1, end[mid]);
		int len_of_mid = e+1-s;
		if (len_of_mid >= k)
			cout << A[mid] << endl;
		else
			cout << "-1" << endl;
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
