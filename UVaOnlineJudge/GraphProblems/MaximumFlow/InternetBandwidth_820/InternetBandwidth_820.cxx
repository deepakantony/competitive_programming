#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

#define REP(i,n) for(int i = 0; i < (n); ++i)
#define FOR(i,s,n) for(int i = (s); i < (n); ++i)
#define INF 1000000000

int res[101][101], parent[101], dist[101];
int gsize;
int s, t, c;

int augment(int u, int flow) {
	if(u != s && parent[u] != -1) {
		int v = parent[u];
		flow = augment(v, min(flow, res[v][u]));
		res[v][u] -= flow;
		res[u][v] += flow;
	}
	return flow==INF? 0: flow;
}

int getFlow() {
	int mf = 0;
	int f = 0;
	do {
		memset(parent, -1, sizeof parent);
		REP(i, gsize) dist[i] = INF;
		int u = s;
		dist[u] = 0;
		queue<int> Q; Q.push(u);
		while(!Q.empty() && Q.front() != t) {
			u = Q.front(); Q.pop();
			REP(v, gsize) if(res[u][v] > 0 && dist[v] == INF) 
				Q.push(v), dist[v] = dist[u]+1, parent[v] = u;
		}
		f = augment(t, INF);
		mf += f;
	} while(f != 0);
	return mf;
}

int main(int argc, char *argv[]) {
	int u,v,w;
	int network = 1;
	while(scanf(" %d", &gsize) != EOF && gsize != 0) {
		gsize++;
		memset(res, 0, sizeof res);
		scanf(" %d %d %d" , &s, &t, &c);
		while(c--) {
			scanf(" %d %d %d" , &u, &v, &w);
			res[u][v] += w;
			res[v][u] = res[u][v];
		}
		int mf = getFlow();

		printf("Network %d\n", network++);
		printf("The bandwidth is %d.\n\n", mf);
	}
	return 0;
}
