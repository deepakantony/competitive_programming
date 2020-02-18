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
#include <set>

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
typedef map<string, int> MapSI;
typedef map<int, int> MapII;

#define REP(i, n) for(int i = 0; i < (n); ++i)
#define FOR(i, st, nd) for(int i = (st); i < (nd); ++i)
#define SET(a, val) memset(a, val, sizeof(a))
#define mp make_pair

#define INF numeric_limits<int>::max()
#define EPS (1e-9)
#define FLT_EQ(x,y) ((fabs((x)-(y))) < EPS)

LL max_profit(const VVI &matrix, set<int> movie_set, set<int> time_set, set<int> cost_set) {
	assert(movie_set.size() == time_set.size());
	assert(movie_set.size() == cost_set.size());

	if(movie_set.size() == 1) {
		int r = *(movie_set.begin());
		int c = *(time_set.begin());
		int cost = *(cost_set.begin());
		return ((matrix[r][c]==0) ? -100 : matrix[r][c]*cost);
	}

	LL best_profit = numeric_limits<LL>::min();
	for(auto m : movie_set) {
		set<int> new_movie_set(movie_set);
		new_movie_set.erase(m);
		for(auto t : time_set) {
			set<int> new_time_set(time_set);
			new_time_set.erase(t);
			for(auto cost: cost_set) {
				set<int> new_cost_set(cost_set);
				new_cost_set.erase(cost);
				LL cur_profit =
					((matrix[m][t]==0) ? -100 : matrix[m][t]*cost) +
					max_profit(matrix, new_movie_set, new_time_set, new_cost_set);

				best_profit = max(best_profit, cur_profit);
			}
		}
	}

	return best_profit;
}

void solve() {
	int T; cin >> T;
	MapSI movie_map{
		{"A", 0},
		{"B", 1},
		{"C", 2},
		{"D", 3}
	};
	MapII time_map{
		{12, 0},
		{3, 1},
		{6, 2},
		{9, 3}
	};

	LL total_profit = 0;
	while(T--) {
		VVI matrix(4, VI(4, 0));
		string m;
		int t;
		LL N; cin >> N;
		REP(i, N) {
			cin >> m >> t;
			int r = movie_map[m];
			int c = time_map[t];
			++matrix[r][c];
		}

		LL cur_max_profit = max_profit(matrix, {0,1,2,3}, {0,1,2,3}, {25,50,75,100});
		cout << cur_max_profit << endl;
		total_profit += cur_max_profit;
	}
	cout << total_profit << endl;
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
