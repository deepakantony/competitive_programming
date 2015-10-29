/*
  Problem: Template CPP main file.
  Link: https://uva.onlinejudge.org/external/3/378.html
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: Line equation is f(x,y) = ax+by+c = 0
  Two lines would be a1x+b1y+c1 =0 & a2x+b2y+c2 = 0
  If the lines are parallel - a1 == a2 && b1 == b2.
  If they are the same lines then a1 == a2 && b1 == b2 && c1 == c2.
  If they intersect, solve for x & y with the two equations.
  if a1 != 0:
    x = (-c1 - b1y)/a1
	y = (-c2 - a2x)/b2 = (-c2 - a2 (-c1 - b1y)/a1 ) /b2
	y = ( -a1c2 + a2c1 + a2b1y )/a1b2
	a1b2y - a2b1y = a2c1 - a1c2
	y = (a2c1-a1c2)/(a1b2-a2b1)
	Then substitute y in the eq for x (above)
  else
    y = -c1/b1
	x = (-c2 - b2y)/a2  --- a2 cannot be 0; if 0 the lines are parallel as a2 == a1 & b2 == b1 when normalized
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
#include <cmath>
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

#define EPS 1e-9
#define FLT_EQ(a,b) (fabs((double)((a)-(b))) < EPS)

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
		a =pt2.y - pt1.y;
		b =pt1.x - pt2.x;
		c =pt2.x*pt1.y - (pt1.x*pt2.y);

		// normalize (ensures comparing lines for equality easier)
		if( !FLT_EQ(a,0) ) {
			a /= a; b /= a; c /= a;
		} else if( b != 0 ) {
			a /= b; b /= b; c /= b;
		}
	}
	Line(LineSegment<T> const &ls ) : Line(ls.pt1, ls.pt2) {}
	
	T SolveForPoint(Point<T> const &pt) {
		return (a * pt.x + b * pt.y + c);
	}

	bool operator==(Line<T> const &other ) const { return a == other.a && b == other.b && c == other.c; }

	bool Parallel(Line<T> const &other) const { return a == other.a && b == other.b; }

	bool Intersects(Line<T> const &other, Point<T> &intersection_point) const {
		if( (*this) == other || Parallel(other) ) return false;
		if( !FLT_EQ(a,0) ) {
			intersection_point.y = (other.a*c - other.c*a)/(a*other.b - other.a*b);
			intersection_point.x = (-c-b*intersection_point.y)/a;
		}
		else { // other.a should not be 0
			assert(other.a != 0);
			intersection_point.y = -c/b;
			intersection_point.x = (-other.c-other.b*intersection_point.y)/other.a;
		}
		return true;
	}
};

template<class T>
ostream& operator<<(ostream &os, Line<T> l) {
	os << "(" << l.a << ", " << l.b << ", " << l.c << ")";
	return os;
}


void solve()
{
	int n_tests;
	cin >> n_tests;
	cout << "INTERSECTING LINES OUTPUT" << endl;
	
	while ( n_tests-- ) {
		int x1,y1, x2,y2, x3,y3, x4,y4;
		cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
		Line<double> l1(Point<double>(x1,y1), Point<double>(x2,y2));
		Line<double> l2(Point<double>(x3,y3), Point<double>(x4,y4));

		cout << l1 << l2 << endl;

		if( l1 == l2 )
			cout << "LINE" << endl;
		else if ( l1.Parallel(l2) )
			cout << "NONE" << endl;
		else {
			Point<double> pt;
			assert( l1.Intersects(l2, pt) );
			cout << "POINT " << fixed << setprecision(2) << pt.x << " " << pt.y << endl;
		}
	}
		
	cout << "END OF OUTPUT" << endl;
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
