// http://www.codechef.com/COOK25/problems/UNFRIEND

#include <cstdio>
#include <cstring>

int G[50][50], N, M;
int visited[50];
int color[50];
int x[200], y[200];

bool isBipartite(int curNode) {
	visited[curNode] = 1;
	bool res = true;
	for(int i = 0; i < N && res == true; ++i)
		if(G[curNode][i]) 
			if(visited[i]) {
				if(color[i] == color[curNode])
					res = false;
			}
			else {
				color[i] = 1-color[curNode];
				res = isBipartite(i);
			}
	return res;
}

// If I remove all the warpable edges from the graph; the solution to the 
// problem is finidng if this reduced graph is bipartite.
bool isBipartite() {
	memset(visited, 0, sizeof visited);
	memset(color, -1, sizeof color);
	bool res = true;
	for(int i = 0; i < N && res == true; ++i)
		if(visited[i] == 0)
			color[i] = 0, res = isBipartite(i);
	return res;
}

int main(int argc, char *argv[])
{
	//freopen("Input_RebuildingByteland.txt", "r", stdin);
	int T, W, wi; scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &N, &M);
		memset(G, 0, sizeof G);
		for(int i = 0; i < M; ++i)
			scanf("%d%d", &x[i], &y[i]), x[i]--, y[i]--, 
				G[x[i]][y[i]] = G[y[i]][x[i]] = 1;
		scanf("%d", &W);
		for(int i = 0; i < W; ++i)
			scanf("%d", &wi), wi--, G[x[wi]][y[wi]] = G[y[wi]][x[wi]] = 0;

		if(isBipartite())
			printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
