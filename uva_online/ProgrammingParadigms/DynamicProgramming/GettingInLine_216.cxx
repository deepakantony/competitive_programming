#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

#define REP(i, st, n) for(int (i) = (st); (i) < (n); ++(i))

double dist[8][8];
int x[8], y[8];
double memo[8][(1<<8)-1];
int backtrack[(1<<8)-1];
int N;

void calculateAllDists()
{
	REP(i,0,N) REP(j,i,N) {
		if(i==j) dist[i][i] = 0.0;
		else dist[i][j] = dist[j][i] = 
				 sqrt((x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]));
	}
}

double TSP(int curCoord, int bitmask)
{
	if(memo[curCoord][bitmask] >= 0.0) return memo[curCoord][bitmask];
	if(bitmask == 0) memo[curCoord][0] = 0.0;
	else if(curCoord == -1) {
		REP(mask, 0, N) {
			double res = TSP(mask, bitmask&(~(1<<mask)));
			if(memo[mask][bitmask] < 0.0 || res < memo[mask][bitmask]) {
				memo[mask][bitmask] = res;
				backtrack[bitmask] = mask;
			}
		}
	}
	else {
		REP(mask, 0, N) 
			if((bitmask&(1<<mask))) {
				double res = dist[curCoord][mask] + 
					TSP(mask, bitmask&(~(1<<mask)));
				if(memo[curCoord][bitmask] < 0.0 || 
				   res < memo[curCoord][bitmask]) {
					memo[curCoord][bitmask] = res;
					backtrack[bitmask] = mask;
				}
			}
	}
	return memo[curCoord][bitmask];
}

void bt(int bitmask)
{
	if(bitmask == 0) return;
	int c1 = backtrack[bitmask];
	bitmask = (bitmask&(~(1<<c1)));
	int c2 = backtrack[bitmask];
	printf("Cable requirement to connect (%d,%d) to (%d,%d) is %.2f feet.\n",
		   x[c1], y[c1], x[c2], y[c2], dist[c1][c2]);
	bt(bitmask);
}

void clearmemo() {
	REP(i, 0, N) REP(j, 0, (1<<N)-1)
		memo[i][j] = -1.f;
		
}

int main(int argc, char *argv[])
{
	int test = 1;
	double res;
	while(scanf(" %d", &N), N!= 0) {
		REP(i, 0, N) scanf(" %d %d", &x[i], &y[i]);
		calculateAllDists();
		clearmemo();
		res = TSP(-1, ((1<<N)-1));
		printf("**********************************************************\n");
		printf("Network #%d\n", test);
		//bt((1<<N)-1);
		printf("Number of feet of cable required is %.2f.\n", res);
		printf("**********************************************************\n");
	}
	return 0;
}
