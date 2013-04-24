/*
  Problem: Sunny Mountains
  Link: http://uva.onlinejudge.org/external/9/920.html
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: Find intersection point between horizontal line and the surface. 
  Then find the distance between intersection point and top point.
*/

#include <cstdio>
#include <cstring>
#include <cassert>
#include <cmath>
#include <ctime>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits>
#include <functional>

using namespace std;

typedef unsigned long long UL;
typedef long long LL;
typedef pair<float,float> PFF;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<LL> VL;
typedef vector<VL> VVL;
typedef vector<PFF> VPFF;
typedef vector<VPFF> VVPFF;

#define REP(i, n) for(int i = 0; i < (n); ++i)
#define FOR(i, st, nd) for(int i = (st); i < (nd); ++i)
#define SET(a, val) memset(a, val, sizeof(a))
#define mp make_pair

#define INF numeric_limits<int>::max()
#define EPS 10E-6
#define FLOAT_EQ(x,y) (((x)+EPS) > y && ((x)-EPS) < y)

PFF find_intersection_point_between_lines(
	PFF line1_point1, PFF line1_point2,
	PFF line2_point1, PFF line2_point2 )
{
	// find line equation Ax+By=C
	float A1 = line1_point2.second - line1_point1.second;
	float B1 = line1_point1.first - line1_point2.first;
	float C1 = A1*line1_point1.first + B1*line1_point1.second;

	float A2 = line2_point2.second - line2_point1.second;
	float B2 = line2_point1.first - line2_point2.first;
	float C2 = A2*line2_point1.first + B2*line2_point1.second;

	float det = A1*B2 - A2*B1;
	if( FLOAT_EQ(det, 0) )
	{
		return mp((float)INF, (float)INF);
	}
	else
	{
		return mp((B2*C1 - B1*C2)/det, (A1*C2 - A2*C1)/det);
	}
}

float distance_between_points(PFF point1, PFF point2)
{
	float side_a = point1.first-point2.first;
	float side_b = point1.second-point2.second;
	return sqrt(side_a * side_a + side_b * side_b);
}

void solve_sunny_mountains() {
	int n_tests, test;
	scanf("%d", &n_tests);
	REP(test, n_tests)
	{
		int N, x, y;
		VPFF points_array;

		scanf("%d", &N);

		REP(coordinate_index, N)
		{
			scanf("%d %d", &x, &y);
			points_array.push_back(mp((float)x,(float)y));
		}

		float total_sunny_mountainsides = 0.f;

		if( N > 0 )
		{
			sort(points_array.begin(), points_array.end(), greater<PFF>());

			PFF previous_point = points_array[0];
			for(int i = 1; i < points_array.size(); i += 2)
			{
				PFF higher_point = points_array[i];
				PFF lower_point = points_array[i-1];

				PFF intersection_point = 
					find_intersection_point_between_lines(
						lower_point, higher_point,
						previous_point, mp(0.f, previous_point.second)
						);

				if( intersection_point.second < (higher_point.second + EPS) )
				{
					total_sunny_mountainsides += 
						distance_between_points(intersection_point, higher_point);
					previous_point = higher_point;
				}
			}
		}

		printf("%.2f\n", total_sunny_mountainsides);
	}
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	solve_sunny_mountains();

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
