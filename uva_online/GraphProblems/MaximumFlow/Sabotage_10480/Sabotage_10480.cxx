#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

#define s 0
#define t 1
#define REP(i,n) for(int i = 0; i < (n); ++i)
#define FOR(i,s,n) for(int i = (s); i < (n); ++i)

typedef queue<int> QI;
typedef unsigned long long vlong;
#define INF -1
vlong res[50][50], dist[50], graph[50][50];
int parent[50];
int gsize, nedges;
vlong flow;

void augment(int u, vlong minflow) {
	if(u == s) flow = minflow;
	else if (parent[u] != -1 ){
		int v = parent[u];
		minflow = min(minflow, res[v][u]);
		augment(v, minflow);
		res[v][u] -= flow;
		res[u][v] += flow;
	}
}

void printMinCut() {
	int mf = 0;
	do {
		memset(parent, -1, sizeof parent);
		memset(dist, INF, sizeof dist);

		dist[s] = 0;
		QI Q; Q.push(s);
		while(!Q.empty() && Q.front() != t) {
			int u = Q.front(); Q.pop();
			REP(v, gsize) if(res[u][v] > 0 && dist[v] == INF)
				Q.push(v), dist[v] = 0, parent[v] = u;
		}
		flow = 0;
		augment(t, INF);
		mf += flow;
	} while(flow != 0);

	QI Q; Q.push(s); 
	memset(dist, INF, sizeof dist);
	dist[s] = 0;
	vector<pair<int,int> > minCutCandidates;
	while(!Q.empty()) {
		int u = Q.front(); Q.pop();
		REP(v, gsize) 
			if(res[u][v] > 0 && dist[v] == INF)
				Q.push(v), dist[v] = 0;
			else if(graph[u][v] > 0 && dist[v] == INF)
				minCutCandidates.push_back(make_pair(u,v));
	}
	REP(i, minCutCandidates.size()) {
		int u = minCutCandidates[i].first;
		int v = minCutCandidates[i].second;
		if(dist[u] == INF || dist[v] == INF)
			printf("%d %d\n", u+1, v+1);
	}

	printf("\n");

}

int main(int argc, char *argv[])
{
	int u, v, w;
	while(scanf(" %d %d", &gsize, &nedges) != EOF &&
		  gsize != 0 && nedges != 0) 
	{
		memset(res, 0, sizeof res);
		memset(graph, 0, sizeof graph);
		while(nedges--) {
			scanf(" %d %d %d", &u, &v, &w);
			--u, --v, res[u][v] = res[v][u] = graph[u][v] = graph[v][u] = w;
		}
		//REP(i, gsize) { REP(j, gsize)printf("%d\t", res[i][j]); printf("\n"); }
		printMinCut();
	}
	return 0;
}
