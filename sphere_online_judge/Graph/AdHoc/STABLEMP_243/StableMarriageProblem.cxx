// Stable marriage problem - using gale shapley algorithm

#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#define REP(i, n) for(int i = 0; i < (n); ++i)
#define FOR(i, st, nd) for(int i = (st); i < (nd); ++i)

typedef vector<int> VI;
typedef vector<VI> VVI;

int main (int argc, char *argv[]) {
	int T; scanf("%d",&T);
	int N, val;

	VVI womenPref(501, VI(501));
	VVI menPref(501, VI(501));

	VI prefIndex(501);
	VI engaged(501);

	while(T--) {
		scanf("%d", &N);

		VI womenMapping(501, 0);

		queue<int> Q;

		// Store both men's and women's preference
		FOR(i, 1, N+1) {
			scanf("%d", &val);
			FOR(j, 1, N+1) 
				scanf("%d", &val), womenPref[i][val] = j;
		}
		FOR(i, 1, N+1) { 
			REP(j, N+1) scanf("%d", &menPref[i][j]); 
			prefIndex[i] = 1;
			Q.push(i);
		}


		// while there are free men
		while(!Q.empty()) {
			// for every man M, pick his most preferred woman W, he has not yet 
			// proposed to.
			int man = Q.front(); Q.pop();
			// remove W from M's preference.
			int curPref = menPref[man][prefIndex[man]++];
			
			// if the woman W is not engaged
			if(womenMapping[curPref] == 0)
				// engage with her, mark M and W as engaged
				womenMapping[curPref] = man, engaged[man] = curPref;
			// if the woman W is engaged and her preference for the man M is 
			// higher 
			else if(womenPref[curPref][man] < 
					womenPref[curPref][womenMapping[curPref]])
				// engage to man M, mark M as engaged, mark the previous man M' 
				// as free
				Q.push(womenMapping[curPref]), 
					womenMapping[curPref] = man,
					engaged[man] = curPref;
			else // push back man M back to the queue
				Q.push(man);
		}

		FOR(i, 1, N+1)
			printf("%d %d\n", i, engaged[i]);
		
	}
	return 0;
}
