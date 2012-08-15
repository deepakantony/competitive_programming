#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits>

using namespace std;

#define REP(i, n) for(int i = 0; i < (n); ++i)
#define FOR(i, st, nd) for(int i = (st); i < (nd); ++i)
#define mp make_pair

typedef long long LL;
typedef pair<int, int> PII;
typedef vector<PII> VPII;

// read input and implement a O(M*log(M))
int main(int argc, char *argv[]) {
	int T; scanf("%d", &T);
	int N, M;
	int w, x, y, z;
	while(T--) {
		scanf(" %d %d",&N, &M);

		VPII mUpdates;
		mUpdates.push_back(mp(N, 0));

		// just store the range updates since the changes happend only at the 
        // ends. 
		REP(upd, M) {
			scanf(" %d %d %d %d", &w, &x, &y, &z);
            if(w == 2) z = -z;
            mUpdates.push_back(mp(x-1, z));
            mUpdates.push_back(mp(y, -z));
		}
		sort(mUpdates.begin(), mUpdates.end());

        int i = 0; // curIndex
		LL a_i = 1;

		LL maxSoFar = numeric_limits<LL>::min();
		LL minSoFar = numeric_limits<LL>::max();
		REP(index, mUpdates.size()) {
			PII cur = mUpdates[index];
            int nexti = cur.first;
			if(nexti != i) {
                maxSoFar = max(maxSoFar, a_i+nexti-i-1);
                minSoFar = min(minSoFar, a_i);
                a_i = a_i+nexti-i;
			}
            a_i += cur.second;
            i = nexti;
		}
        printf("%d\n", maxSoFar-minSoFar);
	}
	return 0;
}


