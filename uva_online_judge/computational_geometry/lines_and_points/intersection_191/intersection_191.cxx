/*
  Problem: Template CPP main file.
  Link:https://uva.onlinejudge.org/external/1/191.html
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution:
  https://stackoverflow.com/questions/99353/how-to-test-if-a-line-segment-intersects-an-axis-aligned-rectange-in-2d/293052#293052
  1. Check if rectangle lies entirely above or below the line (which encompasses line segment)
     * line eq: f(x,y) = ax+by+c = 0
 	 * if f(x,y) > 0 then (x,y) is above the line
	 * if f(x,y) < 0 then (x,y) is below the line
	 * So if all corners of rectangle is above the line or all are below the line then they don't intersect.
  2. If rect is not entirely separated, then check if the x-axis & y-axis project overlap. If they do then they intersect
     * x-axis projection just sets y = 0; simlarly set x = 0 for y-axis projection
	 * rectangles x-axis projection would be min( all x values ) and max( all x values )
	 * same logic for the y-axis
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
	T a,b,c;
	Line( LineSegment<T> const &ls ) {
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
	}
	T SolveForPoint(Point<T> const &pt) {
		return (a * pt.x + b * pt.y + c);
	}
};
template<class T>
struct Rectangle {
	Point<T> pt1,pt2,pt3,pt4;
	Rectangle(Point<T> const &tf, Point<T> const &br)
		: pt1(tf), pt2(tf.x,br.y), pt3(br), pt4(br.x,tf.y) {}

	
	bool Intersects(LineSegment<T> const &ls) const {

		// Check if rectangle is above or below the line
		Line<T> l(ls);
		T fx1,fx2,fx3,fx4;
		fx1 = l.SolveForPoint(pt1); fx2 = l.SolveForPoint(pt2);
		fx3 = l.SolveForPoint(pt3); fx4 = l.SolveForPoint(pt4);
		if( fx1 > 0 && fx2 > 0 && fx3 > 0 && fx4 > 0 ) return false;
		if( fx1 < 0 && fx2 < 0 && fx3 < 0 && fx4 < 0 ) return false;

		// Project both line segment and rectangle and see if there is any overlap
		T minx = min( pt1.x, min( pt2.x, min( pt3.x, pt4.x ) ) );
		T maxx = max( pt1.x, max( pt2.x, max( pt3.x, pt4.x ) ) );
		T miny = min( pt1.y, min( pt2.y, min( pt3.y, pt4.y ) ) );
		T maxy = max( pt1.y, max( pt2.y, max( pt3.y, pt4.y ) ) );
		T minpx = min(ls.pt1.x, ls.pt2.x);
		T maxpx = max(ls.pt1.x, ls.pt2.x);
		T minpy = min(ls.pt1.y, ls.pt2.y);
		T maxpy = max(ls.pt1.y, ls.pt2.y);
		if( maxx < minpx || minx > maxpx ) return false;
		if( maxy < minpy || miny > maxpy ) return false;

		// there is an intersection
		return true;
	}
};

void solve()
{
	int t;
	cin >> t;

	while(t--)
	{
		Point<int> pt1, pt2, tl, br;
		cin >> pt1.x >> pt1.y >> pt2.x >> pt2.y >> tl.x >> tl.y >> br.x >> br.y;

		LineSegment<int> ls(pt1,pt2);
		Rectangle<int> rect(tl,br);

		cout << (rect.Intersects(ls) ? "T" : "F") << endl;
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
