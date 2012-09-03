#include <cstdio>
#include <set>
#include <functional>

using namespace std;

typedef set<int> minset;
typedef set<int, greater<int> > maxset;

#define REP(i, n) for(int i = 0; i < (n); ++i)
#define FOR(i, st, nd) for(int i = (st); i < (nd); ++i)

int main(int argc, char *argv[]) {
	int N, W;
	minset mn;
	maxset mx;
	int allNumbers[400000];
	if(scanf("%d%d", &N, &W) != EOF) {
		int ways = 0;
		REP(i, W) scanf("%d", &allNumbers[i]), 
			mn.insert(allNumbers[i]), mx.insert(allNumbers[i]);
		if((*(mx.begin()) - *(mn.begin())) == (W-1)) ++ways;
		FOR(i, W, N) {
			scanf("%d", &allNumbers[i]);
			mn.erase(allNumbers[i-W]), mx.erase(allNumbers[i-W]);
			mn.insert(allNumbers[i]), mx.insert(allNumbers[i]);
			if((*(mx.begin()) - *(mn.begin())) == (W-1)) ++ways;
		}
		printf("%d\n", ways);
	}
	return 0;
}
