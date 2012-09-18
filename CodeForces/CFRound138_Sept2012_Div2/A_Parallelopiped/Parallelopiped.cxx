/*
  Problem: Parallelepiped
  Link: http://codeforces.ru/problemset/problem/224/A
  Author: deebee
  Solution: Rectangular parallelepiped is a cuboid, easy to calculate perimeter,
  given the three 
*/

#include <cstdio>
#include <cstring>
#include <cassert>
#include <ctime>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long long LL;
typedef unsigned long long UL;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<LL> VL;
typedef vector<VL> VVL;

#define REP(i, n) for(int i = 0; i < (n); ++i)
#define FOR(i, st, nd) for(int i = (st); i < (nd); ++i)
#define SET(a, val) memset(a, val, sizeof(a))

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	// solve something here
	int a1, a2, a3;
	while(scanf("%d%d%d", &a1, &a2, &a3) != EOF) {
		int side1 = (int)sqrt( (double)(a1*a2)/(double)a3);
		int side2 = a1/side1;
		int side3 = a2/side1;
		printf("%d\n", 4*(side1+side2+side3));
	}

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
