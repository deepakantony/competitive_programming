/*
  Problem: Recipe Reconstruction
  Link: http://www.codechef.com/COOK26/problems/RRECIPE
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: Find the number of '?' on the first half which have a corresponding
  '?' on the other half. Raise 26 to that number.
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

#define MOD 10000009

bool isValidPalindrome(char *recipeString, int recipeSize) {
	int recipeSizeHalf = recipeSize/2 + 1;
	REP(i, recipeSizeHalf) 
		if(recipeString[i] != '?' && recipeString[recipeSize-1-i] != '?' &&
		   recipeString[recipeSize-1-i] != recipeString[i])
			return false;
	return true;
}

LL modularPow(LL base, LL exponent, LL mod) {
	int res = 1;
	while(exponent > 0) {
		if(exponent%2) res = (res*base)%mod;
		base = (base*base)%mod;
		exponent >>= 1;
	}
	return res;
}

void solveReipeReconstruction() {
	int T; scanf("%d", &T);
	char recipeString[1000010];
	while(T--) {
		scanf("%s", recipeString);
		int recipeSize = strlen(recipeString);
		if(isValidPalindrome(recipeString, recipeSize)) {

			int recipeSizeHalf = (recipeSize/2) + (recipeSize%2);
			int numOfUnrestricted = 0;
			REP(i, recipeSizeHalf) 
				if(recipeString[i] == '?' &&
					recipeString[recipeSize-1-i] == '?') 
					++numOfUnrestricted;
			printf("%lld\n", modularPow(26, numOfUnrestricted, MOD));
		}
		else printf("0\n");
	}
}


int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	// solve something here
	solveReipeReconstruction();

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
