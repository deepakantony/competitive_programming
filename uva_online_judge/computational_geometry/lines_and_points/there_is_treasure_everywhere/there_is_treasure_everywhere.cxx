/*
  Problem: Template CPP main file.
  Link: https://uva.onlinejudge.org/external/5/587.html
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: find the end coordinate by walking the instructions and then calculate distance
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
#include <sstream>

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

template<class T>
struct Point {
	T x, y;
	Point(T x, T y) : x(x), y(y) {}
	Point() : Point(0,0){}
	Point<T> operator+(Point<T> other) const {
		other += *this;
		return other;
	}
	Point<T> &operator+=(Point<T> const &other) {
		x += other.x; y += other.y;
		return *this;
	}
	double Distance(Point<T> const &other)const {
		T dx = x-other.x; T dy = y - other.y;
		return sqrt( dx*dx + dy*dy );
	}
	template<class Scalar>
	Point<T> operator*(Scalar k) const {
		Point<T> res(x*k, y*k);
		return res;
	}
};

template<class T>
ostream &operator<<(ostream &os, Point<T> const &pt) {
	os << "(" << pt.x << "," << pt.y << ")";
	return os;
}

void solve()
{
	string const directions( "NSEW" );
	map<string,Point<double>> dir_to_point_map {
		{ "N", {0,1} },
		{ "NE", {0.7071067811865475,0.7071067811865475} },
		{ "E", {1,0}},
		{"SE", {0.7071067811865475,-0.7071067811865475} },
		{"S", {0,-1}},
		{"SW", {-0.7071067811865475,-0.7071067811865475} },
		{"W", {-1,0}},
		{"NW", {-0.7071067811865475,0.7071067811865475}}};
														
	string line;
	int map_n = 0;
	while( ( cin >> line ) && line != "END" )
	{
		cout << "Map #" << ++map_n << endl;
		
		//cout << line << endl;
		replace(line.begin(), line.end(), ',', ' ');
		replace(line.begin(), line.end(), '.', ' ');
		stringstream ss(line);

		Point<double> origin(0.,0.);
		Point<double> destination(0.,0.);
		int step; string direction;
		while ( ( ss >> step >> direction ) )
		{
			if( direction.size() == 0 ) break;

			destination += (dir_to_point_map[direction]*step);
			//cout << step << " " << direction << destination << endl;
		}
		double distance = origin.Distance(destination);

		cout << setprecision(3) << fixed << "The treasure is located at " << destination << "." << endl;
		cout << setprecision(3) << fixed << "The distance to the treasure is " << distance << "." << endl;

		cout << endl;
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
