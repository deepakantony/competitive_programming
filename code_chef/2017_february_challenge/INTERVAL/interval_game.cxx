/*
  Problem: Interval game
  Link:
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: Similar to nim game.
  First find the best solution for the interval B[M-1].
  Then find the best solution for the interval B[M-2] using the B[M-1] solution.
  ...
  And go on till B[0].
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
#include <set>
#include <numeric>

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

void sliding_window_sum( const VL &A, int window_size, VL &sum )
{
	if (A.size() < window_size) return;
	sum.assign(A.size()-window_size+1, 0);
	if (sum.empty()) return;
	sum[0] = accumulate(A.begin(),A.begin()+window_size,0);

	for (int i = 1; i < sum.size(); ++i)
		sum[i] = sum[i-1] - A[i-1] + A[i+window_size-1];
}

ostream &operator<<(ostream &os, const multiset<LL> &A)
{
	os << "{ ";
	for (auto it = A.rbegin(); it != A.rend(); ++it) os << *it << ", ";
	os << "}";
	return os;
}

void sliding_window_max( const VL &A, int window_size, VL &mx )
{
	if (A.size() < window_size) return;
	mx.assign(A.size()-window_size+1, 0);
	if (mx.empty()) return;
	multiset<LL> mx_set(A.begin(), A.begin() + window_size);

	for( int i = 0; i < mx.size(); ++i ) {
		mx[i] = *mx_set.rbegin();
		mx_set.erase(mx_set.find(A[i]));
		if ((i+1) < A.size())
			mx_set.insert(A[i+window_size]);
	}
}

ostream &operator<<(ostream &os, const VL &A)
{
	os << "[ (" << A.size() << ") -> ";
	for (auto val : A) os << val << ", ";
	os << "]";
	return os;
}

LL solve(const VL &A, const VL &B)
{
	VL sum;
	VL mx;
	//cout << "A: " << A << endl;
   	//cout << "B: " << B << endl;

	sliding_window_sum(A, B[B.size()-1], sum);
	for (int i = B.size()-2; i >= 0; --i)
	{
		sliding_window_max(sum, B[i]-2-B[i+1]+1, mx);
		//cout << "Sum: "<< B[i+1] << sum << " Max: " << B[i]-2-B[i+1]+1 << mx << endl;
		// new sum 
		sliding_window_sum(A, B[i], sum);
		//cout << "\tNewSum: " << sum << endl;
		// update sum
		for ( int j = 0; j < sum.size(); ++j )
			sum[j] -= mx[j+1];
	}
	//cout << "Sum: " << B[0] << sum << endl;// << " Max: " << B[0]-2-B[1]+1<< mx << endl;
	return ( *max_element(sum.begin(), sum.end()));
}

LL brute_recurse(const VL &A, const VL &B, int ai, int aj, int bi)
{
	if (bi == B.size()) return 0;
	LL mx = numeric_limits<LL>::min();
	for ( int i = ai+1; i < aj && (i+B[bi]) <= aj; ++i ) {
		mx = max<LL>(mx, accumulate(A.begin()+i, A.begin()+i+B[bi], 0) - brute_recurse(A,B,i,i+B[bi]-1,bi+1));
	}
	//cout << "ai " << ai << ", aj " << aj << ", bi " << bi << " - mx: " << mx << endl;
	return mx;
}

LL brute_force(const VL &A, const VL &B)
{

	return brute_recurse(A,B,-1,A.size(),0);
}

void solve()
{
	int T; cin >> T;
	while (T--) {
		int N, M; cin >> N >> M;
		VL A(N,0), B(M,0);
		REP(i,N) cin >> A[i];
		REP(i,M) cin >> B[i];

		cout << solve(A,B) << endl;
		//cout << brute_force(A,B) << endl;
	}
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	solve();

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
