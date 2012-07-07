#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define REP(i,n) for(int i = 0; i < (n); ++i)
#define INF 1000000000

int exist[101];
int G[101][101];

int floydWarshall()
{
	REP(k, 101) REP(i, 101) REP(j, 101) 
		G[i][j] = min(G[i][j], G[i][k]+G[k][j]);

	int sum = 0;
	REP(i, 101) REP(j, 101)
		if(G[i][j] != INF && i != j) sum += G[i][j];
	return sum;
}

int main(int argc, char *argv[])
{
	int u, v;
	int test = 1;
	while(scanf(" %d %d", &u, &v) != EOF && u != 0 && v != 0) {
		REP(i, 101) REP(j, 101) G[i][j] = INF;
		memset(exist, 0, sizeof exist);
		do {
			G[u][v] = 1;
			exist[u] = exist[v] = 1;
			//fprintf(stderr, " %d %d\n", u, v);
		} while(scanf(" %d %d\n", &u, &v) != EOF && u != 0 && v != 0);
		int numOfVerts = 0;
		REP(i, 101) numOfVerts += exist[i];
		//fprintf(stderr, " %d\n", numOfVerts);
		int numOfPairs = numOfVerts*numOfVerts-numOfVerts;
		printf("Case %d: average length between pages = ", test++);
		printf("%.3f clicks\n", (float)floydWarshall()/numOfPairs);
	}

	return 0;
}
