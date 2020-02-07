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

void solve() {
	int N, K; cin >> N >> K;
	VI A(N,0); REP(i, N) cin >> A[i];

	int longest_subarray = 1;
	LL cur_height = A[0];
	LL cur_num_adds = 0;
	int cur_height_index = 0;
	VI temp(N,-1); temp[0] = 0;

	for(int s = 0, e = 1; e < N; ++e) {
		if(A[e] > cur_height) {
			LL new_height = A[e];
			LL new_num_adds = cur_num_adds + ((e-s)*(new_height-cur_height));
			while(new_num_adds > K) {
				new_num_adds -= (new_height - A[s]);
				++s;
			}
			cur_height = new_height;
			cur_num_adds = new_num_adds;
		}
		while((cur_num_adds + cur_height - A[e]) > K) {
			// increment s & update height & num of additions
			if(A[s] < cur_height) {
				cur_num_adds -= (cur_height - A[s]);
				++s;
			}
			else {
				// find new height
				LL new_height = A[s+1];
				for(int i = s+2; i <= e; ++i)
					new_height = max(new_height, (LL)A[i]);
				++s;
				cur_num_adds = cur_num_adds - ((e-s)*(cur_height-new_height));
				cur_height = new_height;
			}
		}

		cur_num_adds += (cur_height-A[e]);
		//if((e-s+1) > longest_subarray)
		{
			//cout << s << " - " << e << " - " << longest_subarray << " : " << cur_num_adds << endl;
		}
		longest_subarray = max(longest_subarray, e-s+1);
	}

	cout << longest_subarray << endl;
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
