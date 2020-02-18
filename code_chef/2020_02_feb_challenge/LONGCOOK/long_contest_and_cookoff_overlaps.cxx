/*
  Problem: Template CPP main file.
  Link:
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution:
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
#include <string>
#include <map>
#include <iterator>

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

bool is_leap_year(int year) {
	return (((year%400)==0) || (((year%4)==0) && ((year%100)!=0)));
}

int find_date_first_friday(int day_1st) {
	int date_first_friday = 0;
	switch(day_1st) {
		case 0:
		date_first_friday = 6;
		break;
		case 1:
		date_first_friday = 5;
		break;
		case 2:
		date_first_friday = 4;
		break;
		case 3:
		date_first_friday = 3;
		break;
		case 4:
		date_first_friday = 2;
		break;
		case 5:
		date_first_friday = 1;
		break;
		case 6:
		date_first_friday = 7;
		break;
	}
	return date_first_friday;
}

int find_date_2nd_last_sunday(int day_1st, int num_days) {
	int day_last = (day_1st+num_days-1)%7;
	int date_2nd_last_sunday = num_days - 7 - day_last;
	return date_2nd_last_sunday;
}

bool month_has_overlapping_contests(int day_1st, int num_days) {
	int date_first_friday = find_date_first_friday(day_1st);
	int date_2nd_last_sunday = find_date_2nd_last_sunday(day_1st, num_days);
	return (date_2nd_last_sunday < (date_first_friday+10)); // if the long contest ends on the day of cookoff, it doesn't overlap
}

int num_days_in_month(int m, int y) {
	const int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	return (((m==2)&&(is_leap_year(y)))? 29 :  days_in_month[m-1] );
}

// prepare data for first 400 years
VI prepare400yrs() {
	int total_months = 400*12;
	VI _400yrs(total_months, 0);

	int cur_m = 1, cur_y = 1;
	// sunday is indexed 0
	int cur_1st = 1; // monday is the first day of year 1 in gregorian calendar
	_400yrs[0] = (month_has_overlapping_contests(cur_1st, num_days_in_month(cur_m, cur_y))) ? 1  : 0;

	for(int i = 1; i < total_months; ++i) {
		cur_1st = (cur_1st+num_days_in_month(cur_m, cur_y))%7;
		if(cur_m==12) ++cur_y;
		cur_m = ((cur_m)%12) + 1;

		_400yrs[i] = _400yrs[i-1] + ((month_has_overlapping_contests(cur_1st, num_days_in_month(cur_m, cur_y))) ? 1  : 0);
	}

	return _400yrs;
}

// return month extended wrapped index into first 400 years
int index_wrap_to_400yrs(int m, int y) {
	// index starts at 0
	--m; --y;

	return 12*(y%400) + m;
}

class OverlappingContests {

public:
	OverlappingContests():
		_400yrs(prepare400yrs()) {}

	int num_contests_in_range(int m1, int y1, int m2, int y2) const
	{
		int i1 = index_wrap_to_400yrs(m1, y1);
		int i2 = index_wrap_to_400yrs(m2, y2);
		bool y1_y2_same_400yr_bin = (((y1-1)/400) == ((y2-1)/400));

		if (y1_y2_same_400yr_bin)
			return (_400yrs[i2] - ((i1 == 0) ? 0 : _400yrs[i1-1]));
		else {
			int y1_y2_dist_in_400yr_bin = (((y2-1)/400) - ((y1-1)/400)) - 1;
			return (_400yrs.back() - ((i1 == 0) ? 0 : _400yrs[i1-1])) +
				_400yrs.back() * y1_y2_dist_in_400yr_bin +
				(_400yrs[i2]);
		}
	}

	private:
		VI _400yrs;
};

void solve() {
	OverlappingContests overlapping_contests;
	int T; cin >> T;
	while(T--) {
		int m1, y1; cin >> m1 >> y1;
		int m2, y2; cin >> m2 >> y2;
		cout << overlapping_contests.num_contests_in_range(m1, y1, m2, y2) << endl;
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
