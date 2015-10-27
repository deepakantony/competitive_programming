/*
  Problem: Template CPP main file.
  Link: https://uva.onlinejudge.org/external/3/378.html
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: 
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

#define EPS 1e-9

bool operator==(double a, double b) { return (abs(a-b) < EPS); }

template<class T>
struct Point {
	T x,y;
	Point() : x(0),y(0){}
	Point(T x, T y) : x(x), y(y){}
};
template<class T>
struct LineSegment {
	Point<T> pt1, pt2;
	LineSegment(Point<T> pt1, Point<T> pt2) : pt1(pt1), pt2(pt2) {}
};
template<class T>
struct Line {
	double a,b,c;
	Line( Point<T> const &pt1, Point<T> const &pt2 ) {
		// slope intercept formula
		// y - y1 = m ( x - x1 )
		// mx - mx1 - y + y1 = 0
	    // m = (y2-y1)/(x2-x1)
		// (y2-y1)x - (y2-y1)x1 - y(x2-x1) + (x2-x1)y1 = 0
		// so
		// a = (y2-y1)
		// b = (x1-x2)
		// c = x2y1-x1y1-y2x1+x1y1 = x2y1-x1y2
		a = ls.pt2.y - ls.pt1.y;
		b = ls.pt1.x - ls.pt2.x;
		c = ls.pt2.x*ls.pt1.y - (ls.pt1.x*ls.pt2.y);

		// normalize (ensures comparing lines for equality easier)
		if( a != 0 ) {
			a /= a; b /= a; c /= a;
		} else if( b != 0 ) {
			a /= b; b /= b; c /= b;
		}
	}
	Line(LineSegment<T> const &ls ) : Line(ls.pt1, ls.pt2) {}
	
	T SolveForPoint(Point<T> const &pt) {
		return (a * pt.x + b * pt.y + c);
	}

	bool operator==(Line<T> const &other ) { return a == other.a && b == other.b && c == other.c; }

	bool Parallel(Line<T> const &other) { return a == other.a && b == other.b; }
};

void solve()
{
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
