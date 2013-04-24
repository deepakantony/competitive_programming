//http://uva.onlinejudge.org/external/109/10938.html
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
#include <cassert>

using namespace std;

#define REP(i, n) for(int i = 0; i < (n); ++i)
#define SET(a, val) memset(a, val, sizeof(a))
typedef vector<int> VI;
typedef vector<VI> VVI;
VVI G;
int p, r; // fleas meeting location

int dist[5010]; // 2*n is INF ;)
int visited[5010];
int  parent[5010];


void findMeetingPoint(int source, int destination) 
{
	SET(visited, 0);
	queue<int> Q;
	dist[source] = 0, visited[source] = 1, parent[source] = source;
	Q.push(source); 
	while(Q.front() != destination && !Q.empty()) {
		int u = Q.front(); Q.pop();
		REP(v, G[u].size()) 
			if(!visited[G[u][v]]) {
				visited[G[u][v]] = 1;
				parent[G[u][v]] = u, dist[G[u][v]] = dist[u]+1;
				Q.push(G[u][v]);
			}
	}

	assert(dist[destination] != 2*G.size());

	int loopLen = dist[destination]/2;
	int cur = destination;
	while(loopLen--) cur = parent[cur];
	if(dist[destination]%2 == 0)
		p = r = cur;
	else p = min(cur, parent[cur]), r = max(cur, parent[cur]);
	++p; ++r;
}

// just run bfs from one location to the other and then find the mid point.
int main(int argc, char *argv[])
{
	int n, u, v, t;
	while(scanf("%d", &n) != EOF && n != 0) {
		G = VVI(n);
		REP(i, n-1) scanf("%d%d", &u, &v), 
			G[u-1].push_back(v-1), G[v-1].push_back(u-1);
		scanf("%d", &t);
		while(t--) {
			scanf("%d%d", &u, &v);
			findMeetingPoint(u-1, v-1);
			if(p == r) printf("The fleas meet at %d.\n", p);
			else printf("The fleas jump forever between %d and %d.\n", p, r);
		}
	}

	return 0;
}
