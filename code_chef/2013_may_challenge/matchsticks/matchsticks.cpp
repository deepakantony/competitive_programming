/*
  Problem: matchsticks
  Link: http://ww2.codechef.com/MAY13/problems/MSTICK
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: segment tree problem
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

typedef struct  segment_tree_
{
	segment_tree_ *p_left, *p_right;
	int left, right, mid;
	int minlr, maxlr;
} segment_tree;

void build_segment_tree(segment_tree *st, int *array, int left, int right)
{
	assert(st != NULL);
	assert(left <= right);
	if(left == right)
	{
		st->p_left = st->p_right = NULL;
		st->left = st->right = st->mid = left;
		st->minlr = st->maxlr = array[left];
		return;
	}

	st->left = left;
	st->right = right;
	st->mid = (left + right)/2;
	st->p_left = new segment_tree;
	build_segment_tree( st->p_left, array, st->left, st->mid );
	st->p_right = new segment_tree;
	build_segment_tree( st->p_right, array, st->mid+1, st->right);
	st->minlr = min( st->p_left->minlr, st->p_right->minlr );
	st->maxlr = max( st->p_left->maxlr, st->p_right->maxlr );
}

void build_segment_tree(segment_tree **st, int *array, int array_size)
{
	*st = new segment_tree;
	build_segment_tree( *st, array, 0, array_size-1 );
}

void get_max_for_range(segment_tree *st, int left, int right, int &maxlr)
{
	assert(st != NULL);
	assert(left <= right);
	assert(st->left <= left && st->right >= right);

	if( st->left == left && st->right == right )
	{
		maxlr = max(maxlr, st->maxlr);
		return;
	}
	
	if( st->p_left->right >= left )
		get_max_for_range( st->p_left, left, min(st->mid, right), maxlr );
	if( st->p_right->left <= right )
		get_max_for_range( st->p_right, max(st->mid+1, left), right, maxlr );
}

void get_min_for_range(segment_tree *st, int left, int right, int &minlr)
{
	assert(st != NULL);
	assert(left <= right);
	assert(st->left <= left && st->right >= right);

	if( st->left == left && st->right == right )
	{
		minlr = min(minlr, st->minlr);
		return;
	}
	
	if( st->p_left->right >= left )
		get_min_for_range( st->p_left, left, min(st->mid, right), minlr );
	if( st->p_right->left <= right )
		get_min_for_range( st->p_right, max(st->mid+1, left), right, minlr );
}

void solve_matchsticks()
{
	int N; 

#ifndef ONLINE_JUDGE
	while(scanf("%d", &N) != EOF) 
#else
		scanf("%d", &N);
#endif
	{
		int burning_rate_array[100000];

		REP(i, N)
		{
			scanf("%d", &(burning_rate_array[i]));
			burning_rate_array[i] *= 10;
		}

		segment_tree *st;
		build_segment_tree(&st, burning_rate_array, N);
	
		int n_queries; scanf("%d", &n_queries);
		REP(i, n_queries)
		{
			int L, R;
			scanf("%d %d", &L, &R);

			int maxlr = 0, minlr = INF;
			int max_left = 0, max_right = 0;

			get_min_for_range(st, L, R, minlr);
			get_max_for_range(st, L, R, maxlr);
			maxlr = minlr + ( maxlr - minlr ) / 2;
			if( L > 0 )
				get_max_for_range(st, 0, L-1, max_left);
			if( R+1 < N )
				get_max_for_range(st, R+1, N-1, max_right);
			int max_outside_lr = max( max_left, max_right ) + minlr;

			// calculate burndown time
			if( maxlr < max_outside_lr )
				printf("%d.%d\n", max_outside_lr / 10, max_outside_lr % 10);
			else
				printf("%d.%d\n", maxlr / 10, maxlr % 10 );
		}
	}
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	solve_matchsticks();

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
