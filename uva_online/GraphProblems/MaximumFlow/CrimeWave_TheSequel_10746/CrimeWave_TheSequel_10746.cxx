#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>

using namespace std;

#define REP(i, n) for(int i = 0; i < (n); ++i)
#define FOR(i, st, nd) for(int i = (st); i < (nd); ++i)
#define EPS 10E-6
#define inf 10E10f
#define SET(a, val) memset(a, val, sizeof(a))

int n, m;
int size;
float cost[45][45];
int flow[45][45];
int cap[45][45];
int path[45];
float dist[45];

// bellman ford for finding the shortest path
float bellmanford() {
	REP(i, size) dist[i] = inf, path[i] = i;

	dist[0] = 0.f;
	path[0] = 0;
	REP(i, size-1) REP(u, size) REP(v, size) {
		if(flow[v][u] > 0 && dist[v] > (dist[u] - cost[v][u] + EPS)) 
			dist[v] = dist[u]-cost[v][u], path[v] = u;
		if(flow[u][v] < cap[u][v] && dist[v] > (dist[u]+cost[u][v]+EPS))
			dist[v] = dist[u]+cost[u][v], path[v] = u;
	}

	return dist[size-1];
}

// update the flow matrix
int augment(int v, int minflow) {
	int u = path[v];
	if(u != v) {
		
		minflow = augment(u, 
						  min(minflow, 
							  flow[v][u]?flow[v][u]:cap[u][v]-flow[u][v]));
		if(flow[v][u]) flow[v][u] -= minflow;
		else flow[u][v] += minflow;
	}
	return minflow;
}

float mf() {

	SET(flow, 0);
	float mincost = 0.f;
	float curmin = 0.f;
	int reqflow = n;
	while( n > 0 && (inf - (curmin = bellmanford())) > EPS ) {
		int minflow = augment(size-1, reqflow);
		mincost += curmin;
		reqflow-=minflow;
		//printf("%d %d %f %f\n", minflow, n, curmin, mincost);
		//if(!minflow) break;
	}
	return mincost;
}

int main(int argc, char *argv[])
{
	while(scanf("%d%d", &n, &m) != EOF && n != 0) {
		size = n+m+2;
		// init
		REP(i, size) REP(j, size) cost[i][j] = 0.f;
		SET(cap, 0);

		// read the vals
		REP(i, n) REP(j, m) 
			scanf("%f", &cost[j+1][i+m+1]), cap[j+1][i+m+1] = 1;
		REP(j, m) cap[0][j+1] = 1;
		REP(i, n) cap[i+m+1][size-1] = 1;

		float mincost = mf();
		printf("%.2f\n", (mincost/n)+EPS);
	}
	return 0;
}



