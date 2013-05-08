/*
  Problem: Name Reduction
  Link: http://ww2.codechef.com/MAY13/problems/NAME1
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: make a table of alphabet count for parents. Use this table to 
  downcount for the childrens names.
*/

#define ONLINE_JUDGE

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

void solve_name_reduction()
{
	char name[400010];
	int alpha_count[26];

	int test; scanf("%d", &test);
	while(test--)
	{
		memset( alpha_count, 0, sizeof(alpha_count) );

		scanf("%s", name);
#ifndef ONLINE_JUDGE
		printf("parents: %s ", name);
#endif
		char* p = name;
		while( *p )
		{
			++alpha_count[ (*p) - 'a' ];
			++p;
		}
		scanf("%s", name);
#ifndef ONLINE_JUDGE
		printf("%s\n", name);
#endif
		p = name;
		while( *p )
		{
			++alpha_count[ (*p) - 'a' ];
			++p;
		}
#ifndef ONLINE_JUDGE
		printf("Starting alpha_count:"); REP(i, 26) printf("%d,",alpha_count[i]); printf("\n");
#endif
		
		int N;
		scanf("%d", &N);

#ifndef ONLINE_JUDGE
		printf("%d Kids: ", N);
#endif

		int print_no = 0;
		while(N--)
		{
			scanf("%s", name);
#ifndef ONLINE_JUDGE
			printf("%s (*p=%c)", name, *p);
#endif
			if( print_no == 0 )
			{
				p = name;
				while( *p )
				{
					if( ( alpha_count[ (*p) - 'a' ]-- ) <= 0 )
					{
						print_no = 1;
						break;
					}
					++p;
				}
			}
		}
#ifndef ONLINE_JUDGE
		printf("\nfinal alpha_count:"); REP(i, 26) printf("%d,",alpha_count[i]); printf("\n");
#endif

		if( print_no == 0 ) printf("YES\n");
		else printf("NO\n");
	}
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	solve_name_reduction();

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
