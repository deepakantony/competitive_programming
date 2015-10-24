/*
  Problem: Template CPP main file.
  Link: https://uva.onlinejudge.org/external/1/152.html
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: loop through all points to find the distance between them
*/

#include <cstdio>
#include <cstring>
#include <cassert>
#include <ctime>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits>
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

typedef unsigned long long UL;
typedef long long LL;
typedef pair<int,int> PII;
typedef pair<int,PII> PIII;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<LL> VL;
typedef vector<VL> VVL;
typedef vector<PII> VPII;
typedef vector<VPII> VVPII;
typedef vector<PIII> VPIII;

#define REP(i, n) for(int i = 0; i < (n); ++i)
#define FOR(i, st, nd) for(int i = (st); i < (nd); ++i)
#define SET(a, val) memset(a, val, sizeof(a))
#define mp make_pair

#define INF numeric_limits<int>::max()

ostream &operator<<(ostream &os, const PIII &val)
{
	os << "( " << val.first << " " << val.second.first << " " << val.second.second << " )";
	return os;
}

template<typename T>
ostream &operator<<(ostream &os, const vector<T> vec)
{
	os << "< ";
	for( int i = 0; i < vec.size(); ++i )
		os << vec[i] << " ";
	os << ">";
	return os;
}

void solve()
{
	int x,y,z;
	VPIII points;
	while( (cin >> x >> y >> z) && (x != 0 || y != 0 || z != 0 ) )
	{
		points.push_back( mp( x, mp( y, z ) ) );
	}

	sort( points.begin(), points.end() );

	int point_count = points.size();
	VI hist(10, 0);
	
	REP(i, point_count )
	{
		x = points[i].first;
		y = points[i].second.first;
		z = points[i].second.second;
		
		FOR(j, i, point_count)
		{
			int a, b, c;
			a = abs(points[j].first - x);
			b = abs(points[j].second.first - y);
			c = abs(points[j].second.second - z);
			int max_dist = max(a,max(b,c));

			if( max_dist >= 10 )
				break;

			double dist = sqrt( a*a + b*b + c*c );
			cout << max_dist << dist << endl;
			if( dist >= 0 && dist < 10)
				hist[(int)(dist)] += 1;
		}
	}

	cout << points << endl;

	REP(i, 10)
		cout << setw(4) << right << hist[i];
	cout << endl;
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
