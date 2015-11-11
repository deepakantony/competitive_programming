/*
  Problem: Template CPP main file.
  Link: https://uva.onlinejudge.org/external/13/1388.pdf
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: 
  Split 10000 by cur size & new size. 
  Find the min distance from current pos to the new pos.
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
	const double circumf = 10000.0;

	int cur_size, new_adds;
	while( cin >> cur_size >> new_adds ) {
		double tot_dist = 0.0;

		if( new_adds > 1 && cur_size > 0 )
		{
			double cur_split = circumf / cur_size;
			double new_split = circumf / new_adds;

			int i = 0;
			double cur_pos = 0.0;
			for( ; cur_pos < (circumf+EPS); ++i, cur_pos = i * cur_split )
			{
				int j = i;
				double new_pos = j * new_split;
				double min_dist = numeric_limits<double>::max();
				for( ; new_pos < (circumf+EPS); ++j, new_pos = j * new_split )
				{
					
				}
			}
		}
		
		cout << tot_dist << "\n";
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
