#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define REP(i, st, n) for(int (i) = (st); (i) < (n); ++(i))

int memo[31][1000];
int N;
int price[1000], weight[1000];

void buildMemo() {
	REP(wt, 0, 31) {
		REP(item, 0, N) {
			memo[wt][item] = 0;
			if(wt >= weight[item]) 
				memo[wt][item] = max(
					memo[wt-weight[item]][item] + price[item],
					memo[wt][item-1]);
		}
	}
}

int main(int argc, char *argv[])
{

	int nTests; scanf(" %d", &nTests);
	int totalPrice, mw, G;
	while(nTests--) {
		scanf(" %d", &N);
		REP(i, 0, N) scanf(" %d %d", &price[i], &weight[i]);

		buildMemo();
		scanf(" %d", &G);
		totalPrice = 0;
		REP(i, 0, G) {
			scanf(" %d", &mw);
			totalPrice += memo[mw][N-1];
		}
		printf("%d\n", totalPrice);
	}
	return 0;
}
