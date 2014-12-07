/*
  Problem: The love letter mystery
  Link: https://www.hackerrank.com/challenges/the-love-letter-mystery
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: compare strings from the two ends of the string; add the difference between the character to the answer.
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

void solve_the_love_letter_mystery()
{
	int T;
	char str[10001];

	scanf(" %d", &T);
	while(T--)
	{
		scanf("%s", str);

		int len = strlen(str);
		int minimum_steps = 0;
		int mid = (len>>1); // len/2
		REP(i, mid)
		{
			minimum_steps += (abs((int)str[i]-(int)str[len-1-i]));
		}
		printf("%d\n", minimum_steps);
	}
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	// solve something here
	solve_the_love_letter_mystery();

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
