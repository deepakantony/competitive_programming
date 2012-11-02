/*
  Problem: Sridhar Likes Travelling
  Link: http://www.codechef.com/NOV12/problems/TOURMAP
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: Eulerian path, but not a circuit. I will just use a map of string
  to a string. And use a cost map of string to a number.
*/

#include <cstdio>
#include <cstring>
#include <cassert>
#include <ctime>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits>
#include <map>
#include <string>

using namespace std;

typedef unsigned long long UL;
typedef long long LL;
typedef pair<int,int> PII;

typedef pair<string, string> PSS;
typedef pair<string, LL> PSL;

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

void solveSridharLikesTravelling() {
	int T; scanf("%d", &T);
	char fromCity[55], toCity[55];
	LL cost, costSum;
	int N;
	map<string, string> cityToCityMap;
	map<string, LL> cityToCostMap;
	while(T--) {
		scanf("%d", &N);
		costSum = 0;
		cityToCityMap.clear();
		cityToCostMap.clear();

		REP(card, N-1) {
			scanf("%s %s %lld$", fromCity, toCity, &cost);
			string from(fromCity);
			string to(toCity);

			cityToCityMap[from] = to;
			cityToCostMap[to] = cost;
			if(cityToCostMap.find(from) == cityToCostMap.end())
				cityToCostMap[from] = 0;

			costSum += cost;
		}
		
		map<string, LL>::iterator it = cityToCostMap.begin();
		string startCity;
		for(; it != cityToCostMap.end(); ++it)
			if(it->second == 0) {
				startCity = it->first;
				break;
			}
		
		map<string, string>::iterator it2;
		while((it2=cityToCityMap.find(startCity)) != cityToCityMap.end()) {
			printf("%s %s %lld$\n", 
				   startCity.c_str(), 
				   it2->second.c_str(),
				   cityToCostMap[it2->second]);
			startCity = it2->second;
		}
		printf("%lld$\n", costSum);
	}
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	// solve something here
	solveSridharLikesTravelling();

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
