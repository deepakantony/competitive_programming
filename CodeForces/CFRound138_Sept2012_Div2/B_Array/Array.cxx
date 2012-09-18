/*
  Problem: Array
  Link: http://codeforces.com/contest/224/problem/B
  Author: deebee
  Solution: first find if such a segment is possible. If so, initialize l, r
  with the first such possible segment. At each loop, increment r and then try
  to increment l till the point where next l would break the rule. Calculate
  minimum so far. To know when you might break the rule of K distinct I use a 
  hash table that stores the count of each number.
  TIME UP
*/

#include <cstdio>
#include <cstring>
#include <cassert>
#include <ctime>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

typedef long long LL;
typedef unsigned long long UL;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<LL> VL;
typedef vector<VL> VVL;
typedef pair<int, int> PII;

#define REP(i, n) for(int i = 0; i < (n); ++i)
#define FOR(i, st, nd) for(int i = (st); i < (nd); ++i)
#define SET(a, val) memset(a, val, sizeof(a))

#define MAX_SIZE 100100

int arr[MAX_SIZE];
int hashTable[MAX_SIZE];

void solveArray() {
	int N, K, distinct;
	while(scanf("%d%d", &N, &K) != EOF) {
		SET(hashTable, 0);
		scanf("%d", &arr[0]), ++hashTable[arr[0]], distinct = 1;
		int l=0, r=0;
		FOR(i, 1, N) {
			scanf("%d", &arr[i]);
			if(distinct < K) {
				if(!hashTable[arr[i]]) ++distinct, r = i;
				++hashTable[arr[i]];
			}
		}

		if(distinct < K) printf("-1 -1\n");
		else {
			int minSofar = MAX_SIZE;
			int minl = 0, minr = r;
			while(r < N) {
				// update l
				while(l < r) {
					assert(hashTable[arr[l]] > 0);
					if(hashTable[arr[l]] > 1)
						hashTable[arr[l++]]--; // incr l & decr count in table
					else if(hashTable[arr[l]] == 1) {
						if(distinct > K) 
							hashTable[arr[l++]]--, --distinct;
						else break;
					}
				}
				if( minSofar > (r-l+1)) {
					minSofar = r-l+1;
					minl = l;
					minr = r;
				}
				r++;
				if(r < N) ++hashTable[arr[r]];
			}
			printf("%d %d\n", minl+1, minr+1);
		}
	}
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	// solve something here
	solveArray();
#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
