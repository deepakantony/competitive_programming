/*
  Problem: Template CPP main file.
  Link: https://www.codechef.com/APRIL16/problems/COLOR
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: simple!
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

#include <map>

void solve()
{


	int T; cin >> T;
	while(T--)
	{
		map<char,int> RGB; RGB['R'] = RGB['G'] = RGB['B'] = 0;
		int N; cin >> N;
		while( N-- ) {
			char c; cin >> c;
			RGB[c] += 1;
		}
		//cout << RGB['R'] << " " << RGB['G'] << " " << RGB['B'] << endl;
		cout << RGB['R']+RGB['G']+RGB['B']-max(RGB['R'],max(RGB['G'],RGB['B'])) << endl;

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
