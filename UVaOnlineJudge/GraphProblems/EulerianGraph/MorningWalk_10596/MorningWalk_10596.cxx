#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
#define pb push_back

// check if there is a eulerian circuit
//  * treat every edge bidirectional
//  * the correct way would be check if I can reach all roads

// TO GET ACCEPT JUST CHECK IF THE DEGREE OF EVERY VERTEX IS NON ZERO EVEN
int main(int argc, char *argv[])
{
	int n, r; // intersections and roads
	int u, v, possible;
	VVI G;
	int visited[205];
	while(scanf("%d%d", &n, &r) != EOF) {
		G.clear();
		G = VVI(n);

		for(int i = 0; i < r; ++i) 
			scanf("%d%d", &u, &v), G[u].pb(v), G[v].pb(u);

//		memset(visited, 0, sizeof(visited));
//		queue<int> Q;
//		Q.push(0); visited[0] = 1;
//		while(!Q.empty()) {
//			int u = Q.front(); Q.pop();
//			for(int i = 0; i < G[u].size(); ++i) {
//				int v = G[u][i];
//				if(!visited[v]) visited[v] = 1, Q.push(v);
//			}
//		}
//		
		possible = 1;
		for(int i = 0; i < G.size(); ++i) {
			//printf("%d\n", G[i].size());
			if((G[i].size() == 0 || G[i].size()%2 == 1)) {
				possible = 0;
				break;
			}
		}
		printf("%s\n", possible?"Possible":"Not Possible");
	}
	return 0;
}

