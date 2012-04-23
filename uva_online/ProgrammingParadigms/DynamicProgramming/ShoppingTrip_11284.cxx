#include <cstdio>
#include <vector>

using namespace std;

#define REP(i, st, n) for(int (i) = (st); (i) < (n); ++(i))

bool isBitOn(int num, int pos) { return (num&(1<<pos)) != 0; }
int unsetBit(int num, int pos) { return (num&(~(1<<pos))); }

int dist[13][13];
int memo[13][(1<<13)-1];
int nDVD;

int TSP(int curpos, int bitmask) {
	if(memo[curpos][bitmask] == -1) {
		if(bitmask == 0) memo[curpos][bitmask] = dist[curpos][0];
		else {
			REP(pos, 1, nDVD) {
				if(isBitOn(bitmask, pos)) {
					int res = TSP(pos, unsetBit(bitmask, pos));
					if(memo[curpos][bitmask] == -1 ||
					   res < memo[curpos][bitmask])
						memo[curpos][bitmask];
				}
			}
		}
	}
	return memo[curpos][bitmask];
}

int TSP() {
	return TSP(0, unsetBit((1<<nDVD)-1, 0));
}

VVI adjList;

