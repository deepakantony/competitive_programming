/*
  Problem: Template CPP main file.
  Link: https://uva.onlinejudge.org/external/8/833.pdf
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: Line equation is f(x,y) = ax+by+c = 0
  when b = 1, point is above the line when f(x,y) > 0, below the line f(x,y) < 0 or on when = 0.
  
  For each source:
     source_line_segment_map = [ list of line segments below the point i.e. point projects down to the line ]
	 
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
ostream& operator<<(ostream &os, Point<T> p) {
	os << "(" << p.x << ", " << p.y << ")";
	return os;
}

template<class T>
struct LineSegment {
	Point<T> pt1, pt2;
	LineSegment(Point<T> pt1, Point<T> pt2) : pt1(pt1), pt2(pt2) {}
};
template<class T>
ostream& operator<<(ostream &os, LineSegment<T> l) {
	os << "[" << l.pt1 << ", " << l.pt2 << "]";
	return os;
}

// custom operator< for this problem
// Sort by the y coordinate
template<class T>
bool operator<(const LineSegment<T> &lhs, const LineSegment<T> &rhs) {
	return (min(lhs.pt1.y, lhs.pt2.y) > min(rhs.pt1.y, rhs.pt2.y));
}

template<class T> struct Line;
template<class T>
ostream& operator<<(ostream &os, Line<T> l) {
	os << "(" << l.a << ", " << l.b << ", " << l.c << ")";
	return os;
}

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

		if( !FLT_EQ(a,0) || !FLT_EQ(b,0) )
		{
			// normalize (ensures comparing lines for equality easier)
			double denom = ( !FLT_EQ(b,0) ) ? b : a;
			a /= denom; b /= denom; c /= denom;
		}
		else c = 0.0; // a == b == c == 0; NOT a line at all; but we'll allow this
	}
	Line(LineSegment<T> const &ls ) : Line(ls.pt1, ls.pt2) {}
	
	double SolveForPoint(Point<T> const &pt) {
		return (a * pt.x + b * pt.y + c);
	}

	bool operator==(Line<T> const &other ) const {
		return FLT_EQ(a,other.a) && FLT_EQ(b,other.b) && FLT_EQ(c,other.c);
	}

	bool Parallel(Line<T> const &other) const {
		return FLT_EQ(a,other.a) && FLT_EQ(b,other.b);
	}

	bool Intersects(Line<T> const &other, Point<T> &intersection_point) const {
		if( (*this) == other || Parallel(other) ) return false;
		if( !FLT_EQ(a,0) ) {
			intersection_point.y = (other.a*c - other.c*a)/(a*other.b - other.a*b);
			intersection_point.x = (-c-b*intersection_point.y)/a;
		}
		else { // other.a should not be 0
			//cout << *this << other << endl;
			assert(other.a != 0);
			
			intersection_point.y = -c/b;
			intersection_point.x = (-other.c-other.b*intersection_point.y)/other.a;
		}
		return true;
	}
};

template<class T>
bool PointXProjectionIntersectsLineSegment(Point<T> const &pt, LineSegment<T> const &ls)
{
	T minx = min(ls.pt1.x, ls.pt2.x);
	T maxx = max(ls.pt1.x, ls.pt2.x);
	Line<T> l(ls);
	double fxy = l.SolveForPoint(pt);
	//cout << l << " " << fxy << " ";
	return (pt.x >= minx && pt.x <= maxx && fxy > (0.0-EPS));
}

void solve()
{
	int n_tests; cin >> n_tests;

	while( n_tests-- ){
		int n_ls;
		cin >> n_ls;
		vector<LineSegment<int>> ls_list;
		while(n_ls--) {
			int x1,y1,x2,y2;
			cin >> x1 >> y1 >> x2 >> y2;
			ls_list.push_back(LineSegment<int>(Point<int>(x1,y1), Point<int>(x2,y2)));
		}
		sort(ls_list.begin(), ls_list.end());
		int n_srcs;
		cin >> n_srcs;
		while( n_srcs-- ) {
			int x,y;
			cin >> x >> y;
			Point<int> pt(x,y);
			for(const LineSegment<int> &ls : ls_list) {
				bool pt_p_ls = PointXProjectionIntersectsLineSegment( pt, ls );
				//cout << pt << ls << pt_p_ls << endl;
				if ( pt_p_ls ) pt = ( ls.pt1.y < ls.pt2.y ) ? ls.pt1 : ls.pt2;
			}

			cout << pt.x << endl;
		}
		if( n_tests ) cout << endl;
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
