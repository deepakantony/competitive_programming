/*
  Problem: Little Elephant And Order
  Link: http://www.codechef.com/OCT12/problems/LUCKY10
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: Calculate the following for each string, number of 7's, number of 
  6's and 5's, number of 4's and numbers less than 4. 
  Choose the sum that has the least sum of all these numbers.
  The final answer is, 
  7s = n7s of chosen string + 
           (addtional7s = min(n7s in the other string, 
		   n6s+n5s+n4s+n<4s in chosen string))
  4s = min(n4s of chosen string + n4s of the other string, 
           min(n4s+n<4s in the other string,
		       min(n4s+n<4s of chosen string, 
			       n6s+n5s+n4s+n<4s in chosen string - additional 7s)))
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

struct StringProperties {
	StringProperties() : n7s(0), n65s(0), n4s(0), n3210s(0) {}
	int n7s, n65s, n4s, n3210s;
};

void findProperties(char *str, int len, StringProperties &prop) {
	REP(i, len) 
		if(str[i] == '7') ++prop.n7s;
		else if(str[i] == '6' || str[i] == '5') ++prop.n65s;
		else if(str[i] == '4') ++prop.n4s;
		else if(str[i] >= '0' && str[i] <= '3') ++prop.n3210s;
}

void calculateFinalString(const StringProperties &propChosen, 
						  const StringProperties &propOther, 
						  char *res) {
	int non7sInChosen = propChosen.n65s + propChosen.n4s + propChosen.n3210s;
	int additional7s = min(propOther.n7s, non7sInChosen);
	//int y = min(propChosen.n4s, non7sInChosen-x);
	int sevens = propChosen.n7s + additional7s;
	
	int fours = min(propChosen.n4s + propOther.n4s, 
					min(propOther.n4s + propOther.n3210s,
						min(propChosen.n4s + propChosen.n3210s,
							non7sInChosen - additional7s)));

	int curLoc = 0;
	//fprintf(stderr, "--%d %d %d %d %d\n", non7sInChosen, x, y, sevens, fours);
	REP(i, sevens) res[curLoc++] = '7';
	REP(j, fours) res[curLoc++] = '4';
	res[curLoc] = '\0';
}

void solveLittleElephantAndOrder() {
	int T; scanf("%d", &T);
	char A[20010], B[20010], res[20010];

	int lenA, lenB, sumA, sumB;

	while(T--) {
		StringProperties propA, propB;
		scanf("%s%s", A, B);
		lenA = strlen(A);
		lenB = strlen(B);
		findProperties(A, lenA, propA);
		findProperties(B, lenB, propB);
		sumA = propA.n7s+propA.n65s+propA.n4s+propA.n3210s;
		sumB = propB.n7s+propB.n65s+propB.n4s+propB.n3210s;

		if(sumA > sumB) calculateFinalString(propB, propA, res);
		else calculateFinalString(propA, propB, res);
		printf ("%s\n", res);
	}
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	// solve something here
	solveLittleElephantAndOrder();

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
