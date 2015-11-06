/*
  Problem: Template CPP main file.
  Link: https://uva.onlinejudge.org/external/8/837.pdf
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution:
  Sort end points. The min_x of two ends gets the transperancy_coefficient, 
  while the other gets the reciprocal. Multiply with the coefficient as we go 
  through the points and we get the desired output.
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

bool dbl_eq(double x, double y) { return FLT_EQ(x,y); }

typedef map<double, double> mdd;


void solve()
{
	int n_cases; cin >> n_cases;
	while(n_cases--)
	{
		int nl; cin >> nl;

		mdd pt_2_coef;
		while(nl--)
		{
			double x1,y1,x2,y2,coef;
			cin >> x1 >> y1 >> x2 >> y2 >>coef;
			double minx = min(x1,x2);
			double maxx = max(x1,x2);

			pt_2_coef[minx] = coef;
			pt_2_coef[maxx] = 1.0/coef;
		}

		double cur_coef = 1.0;
		cout << pt_2_coef.size() + 1 << "\n";
		cout << "-inf ";
		for( auto v : pt_2_coef )
		{
			// cout << v.first <<  " " << v.second << "\n";
			cout << fixed << setprecision(3)  << v.first << " " << cur_coef << "\n";
			cout << fixed << setprecision(3) << v.first << " ";
			cur_coef *= v.second;
		}
		cout << "+inf 1.000\n";
		if( n_cases > 0 ) cout << "\n";
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
