// http://uva.onlinejudge.org/external/105/10594.html

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
#include <utility>
#include <iterator>

using namespace std;

typedef pair<int, int> PII;
typedef vector<PII> VPII;
typedef vector<VPII> VVPII;
typedef vector<int> VI;
typedef priority_queue<PII, VPII, greater<PII> > pq;
typedef unsigned int UI;
typedef long long LL;
typedef unsigned long long ULL;

#define SET(a, val) memset(a, val, sizeof(a))
#define ASSIGN(a, val, size) for(int i = 0; i < (size); ++i) a[i] = val
#define REP(i, n) for(int i = 0; i < (n); ++i)
#define FOR(i, st, nd) for(int i = (st); i < (nd); ++i)
#define mp make_pair
#define pb push_back
#define inf 1000000000

LL res[101][101];
LL cost[101][101];
int path[101];
LL dist[101];
VVPII G;
int N, M;
ULL D, K;

// Using shortest path instead of bfs for finding the augmenting path from 
// s to t. This gives us the optimal solution.
// This function updates the path and returns the smallest cost of the path.
// Returns -1 is there is no path.
LL bellmanford(int source, int destination) {
	ASSIGN(dist, inf, N+1);
	dist[source] = 0;
	SET(path, -1);
	REP(i, N-1) FOR(u, 1, G.size()) REP(j, G[u].size()) {
		int v = G[u][j].first;
		int w = G[u][j].second;
		if(res[u][v] > 0 && dist[u]+w < dist[v]) 
			path[v] = u, dist[v] = dist[u]+w;
	}
	//printf("%d\n", dist[destination]);
	return dist[destination];
}
		
		
LL dijkstras(int source, int destination)
{
	ULL dist[101]; SET(dist, -1); // set to inf
	dist[source] = 0;
	pq Q; Q.push(mp(0,source));
	// init path to -1
	SET(path, -1); 
	while(!Q.empty()) {
		int u = Q.top().second; Q.pop();
		REP(i, G[u].size()) {
			int v = G[u][i].first, w = G[u][i].second;
			if(res[u][v] > 0 && dist[u]+w < dist[v]) {
				dist[v] = dist[u]+w;
				path[v] = u;
				Q.push(mp((int)dist[v], v));
			}
		}
	}
	
	return dist[destination];
}


// Based on the path array, update the residual graph
ULL augment(int cur, ULL minflow) {
	if(path[cur] == -1) return minflow;
	else {
		minflow = augment(path[cur], min(minflow, (ULL)res[path[cur]][cur]));
		res[path[cur]][cur] -= minflow;
		res[cur][path[cur]] += minflow;
		//G[cur].pb(mp(path[cur], dist[path[cur]] - dist[cur]));
	}
	return minflow;
}

ULL mf() {
	unsigned long long int mincost = 0;
	LL curCost = 0;
	while(D > 0 && (curCost = bellmanford(1, N)) != inf) {
		ULL minflow = augment(N, D);
		//fprintf(stderr, "D:%d minflow:%d curcost:%d\n",D, minflow, curCost);
		mincost += (curCost*minflow);
		D -= minflow;
	}
	return mincost;
}
	

int main(int argc, char *argv[]) 
{
	while(scanf("%d %d", &N, &M)!= EOF) {
		G = VVPII(N+1);
		int u, v, w;
		while(M--) scanf("%d%d%d", &u,&v,&w), G[u].pb(mp(v,w)), G[v].pb(mp(u,w));

		scanf("%d %d", &D, &K);

		SET(res, 0); SET(cost, 0);
		FOR(i, 1, G.size()) REP(j, G[i].size())
			res[i][G[i][j].first] = K, cost[i][G[i][j].first]=G[i][j].second;

		ULL mc = mf();
		if(D) printf("Impossible.\n");
		else printf("%llu\n", mc);
	}
	return 0;
}

