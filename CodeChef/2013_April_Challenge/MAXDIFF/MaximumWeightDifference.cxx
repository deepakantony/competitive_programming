/*
  Problem: Maximum Weight Difference
  Link: http://www.codechef.com/APRIL13/problems/MAXDIFF
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: Sum up the entire items weights = T; T_small = find the sum of 'n' 
  min weight items using where n = MIN(K, N-K). 
  Final ans = T - T_small - T_small = T - 2 * T_small
*/

#include <cstdio>
#include <cstring>
#include <cassert>
#include <ctime>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits>

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

void solve_maximum_weight_difference()
{
	int num_of_tests;
	int test;

	int weight;
	int weight_index;
	int N, K;
	int total_sum_of_weights;
	int sum_of_weights_of_small_partition;
	int num_of_items_in_small_partition;

	scanf("%d", &num_of_tests);

	REP(test, num_of_tests)
	{
		scanf("%d %d", &N, &K);

		VI weights_array;
		total_sum_of_weights = 0;
		REP(weight_index, N)
		{
			scanf("%d", &weight);
			weights_array.push_back(weight);
			total_sum_of_weights += weight;
		}

		sort(weights_array.begin(), weights_array.end());

		num_of_items_in_small_partition = min(K, N-K);
		sum_of_weights_of_small_partition = 0;
		REP(weight_index, num_of_items_in_small_partition)
		{
			sum_of_weights_of_small_partition += weights_array[weight_index];
		}

		fprintf(stdout, "%d\n", total_sum_of_weights - (2 * sum_of_weights_of_small_partition) );
	}
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	// solve something here
	solve_maximum_weight_difference();

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
