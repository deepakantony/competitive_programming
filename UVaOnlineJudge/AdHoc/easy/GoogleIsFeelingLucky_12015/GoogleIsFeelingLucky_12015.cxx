/*
  Problem: Google Is Feeling Lucky
  Link: http://uva.onlinejudge.org/external/120/12015.html
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: Just list the highest relevance.
*/

#include <cstdio>
#include <cstring>
#include <cassert>
#include <ctime>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits>
#include <string>

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

void solve()
{
	int T;
	scanf("%d", &T);
	char url[1000];
	int relevance;


	REP(test, T) {
		int maxR = 0;
		vector<string> urls;
		REP(i, 10) {
			scanf("%s %d", url, &relevance);
			if(relevance > maxR) {
				urls.clear();
				urls.push_back(url);
				maxR = relevance;
			}
			else if(relevance == maxR) {
				urls.push_back(url);
			}
		}
		printf("Case #%d:\n", test+1);
		REP(i, urls.size())
			printf("%s\n", urls[i].c_str());
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
