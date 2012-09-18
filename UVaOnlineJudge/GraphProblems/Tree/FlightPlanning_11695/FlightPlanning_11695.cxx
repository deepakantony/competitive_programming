#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

#define REP(i, n) for(int i = 0; i < (n); ++i)
#define FOR(i, st, nd) for(int i = (st); i < (nd); ++i)
#define SET(a, val) memset(a, val, sizeof(a))
#define pb push_back

typedef vector<int> VI;
typedef vector<VI> VVI;

VVI G;
int dist[2510][2510];
int parent[2510][2510];
int visited[2510];

int maxflights, max_u, max_v, middle_u, middle_v;
int cancelled_u, cancelled_v;
int new_u, new_v;

void apsp() {
	queue<int> Q;
	maxflights = -1;
	
	// find all pair shortest paths
	// The longest among this is the one to break in the middle.
	REP(source, G.size()) {
		SET(visited, 0);
		dist[source][source] = 0, parent[source][source] = source;
		visited[source] = 1;
		Q.push(source);
		if(maxflights < 0) 
			maxflights = 0, max_u = max_v = source;

		while(!Q.empty()) {
			int u = Q.front(); Q.pop();
			REP(i, G[u].size()) {
				int v = G[u][i];
				if(!visited[v]) {
					visited[v] = 1;
					dist[source][v] = dist[source][u] + 1;
					parent[source][v] = u;
					Q.push(v);
					if(maxflights < dist[source][v]) 
						maxflights = dist[source][v], max_u = source, max_v = v;
				}
			}
		}
	}
}

void findMiddleOfThePath(int u, int v) {
	int halfWay = dist[u][v]/2;
	middle_u = v;
	REP(i, halfWay) middle_u = parent[u][middle_u];
	middle_v = middle_u, middle_u = parent[u][middle_u];
}

void removeEdge(int u, int v) {
	REP(i, G[u].size()) if(G[u][i] == v) {
		swap(G[u][i], G[u][G[u].size()-1]);
		G[u].pop_back();
		break;
	}
	REP(i, G[v].size()) if(G[v][i] == u) {
		swap(G[v][i], G[v][G[v].size()-1]);
		G[v].pop_back();
		break;
	}
}
	
void addNewEdge(int u, int v) {	
	G[u].pb(v), G[v].pb(u);
}

void bfs(int source, VI &connected) {
	connected.clear(); 
	SET(visited, 0);
	visited[source] = 1; connected.pb(source);
	queue<int> Q; Q.push(source);
	while(!Q.empty()) {
		int u = Q.front(); Q.pop();
		REP(i, G[u].size()) {
			int v = G[u][i];
			if(!visited[v]) visited[v] = 1, connected.pb(v), Q.push(v);
		}
	}
}

int middleVertex(const VI &connected) {
	// first find the longest path.
	int longest = -1;
	int longest_u, longest_v;
	REP(i, connected.size()) FOR(j, i, connected.size())
		if(longest < dist[connected[i]][connected[j]]) {
			longest = dist[connected[i]][connected[j]];
			longest_u = connected[i], longest_v = connected[j];
		}

	int middle = longest_v;
	int halfway = (longest+1)/2;
	REP(i, halfway) middle = parent[longest_u][middle];
	// printf(" %d %d %d %d\n", longest, longest_u, longest_v, middle);
	return middle;
}

void solve() {
	apsp();
	if(maxflights == 3)
		cancelled_u = parent[max_u][max_v], cancelled_v = max_v;
	else {
		findMiddleOfThePath(max_u, max_v);
		cancelled_u = middle_u, cancelled_v = middle_v;
	}

	//REP(i, G.size()) { REP(j, G.size()) printf("%d\t", dist[i][j]); printf("\n"); }

	removeEdge(cancelled_u, cancelled_v);
			
	// Find all vertices connected to cancelled_u and find the longest among
	// them. Find it's center, new_u
	VI connected;
	bfs(cancelled_u, connected);
	new_u = middleVertex(connected);

	// Find all vertices connected to cancelled_v and find the longest among
	// them. Find it's cener, new_v
	connected.clear();
	bfs(cancelled_v, connected);
	new_v = middleVertex(connected);

	addNewEdge(new_u, new_v);

	apsp();
}

// remove the center edge and join the centers of the two components.
int main(int argc, char *argv[]) {
	int T; scanf("%d", &T);
	int N, u, v;
	while(T--) {
		scanf("%d", &N);
		G = VVI(N);
		REP(i, N-1) scanf("%d%d", &u, &v), G[u-1].pb(v-1), G[v-1].pb(u-1);

		solve();
		printf("%d\n", maxflights);
		printf("%d %d\n", cancelled_u+1, cancelled_v+1);
		printf("%d %d\n", new_u+1, new_v+1);
	}
	return 0;
}
