#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

#define REP(i, n) for(int i = 0; i < (n); ++i)
#define FOR(i, st, nd) for(int i = (st); i < (nd); ++i)
#define SET(a, val) memset(a, val, sizeof(a))
#define INF 1000000000000000llu

typedef unsigned long long ULL;
int M, W, size;
int res[105][105];
int parent[105];
int visited[105];

// bfs - path from s to t
bool bfs(int source, int destination) {
	SET(parent, -1);
	SET(visited, 0);
	visited[source] = 1;
	queue<int> Q; Q.push(source);
	while(!Q.empty() && Q.front() != destination) {
		int u = Q.front(); Q.pop();
		FOR(v, 1, size)
			if(!visited[v] && res[u][v] > 0)
				parent[v] = u, visited[v] = 1, Q.push(v);
	}
	return parent[destination] != -1;
}

// find the smallest flow through this path 
ULL augment(int v, ULL minflow) {
	int u = parent[v];
	if(u != -1) {
		minflow = augment(u, min(minflow, (ULL)res[u][v]));
		res[u][v] -= minflow;
		res[v][u] += minflow;
	}
	return minflow;
}

// returns the minimum cost to disconnect node 1 from node M
ULL mc() {
	ULL mincut = 0;
	ULL minflow = 0;
	while( bfs(1, size-1) && // path exists from s to t
		   (minflow = augment(size-1, INF)) > 0llu) // flow exists
		mincut += minflow;
	return mincut;
}

// For this problem expand every vertex into 2 vertices and add an edge with
// weight equal to it's cost. And then it's a problem to find the minimum
// cut.
int main(int argc, char *argv[]) {
	int u, v, w;
	while(scanf("%d%d",&M,&W)!=EOF && M!=0) {
		size = (M<<1)+1;
		SET(res, 0); 
		int sum = 0;
		// read the machine's cost
		REP(i, M-2) 
			scanf("%d%d",&u,&w),res[(u<<1)-1][u<<1] = w, sum += w;

		// read the wire's cost
		REP(i, W) {
			scanf("%d%d%d", &u, &v, &w);
			res[u<<1][(v<<1)-1] = w; 
			res[v<<1][(u<<1)-1] = w;
			sum += 2*w;
		}
		res[1][2] = sum+10;
		res[size-2][size-1] = sum+10;

		printf("%llu\n", mc());
		fflush(stdout);
	}
	return 0;
}

