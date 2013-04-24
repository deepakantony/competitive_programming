#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <utility>
#include <list>

using namespace std;

typedef pair<int, int> PII;
typedef vector<PII> VPII;
typedef vector<VPII> VVPII;
typedef vector<int> VI;
typedef list<int> LI;
typedef LI::iterator L_ITER;

#define REP(i, n) for(int i = 0; i < (n); ++i)
#define FOR(i, st, nd) for(int i = (st); i < (nd); ++i)
#define mp make_pair
#define pb push_back

VVPII G;
LI path;

bool isEulerian() {
	REP(i, G.size()) if(G[i].size() % 2) return false;
	return true;
}

void eulerPath(LI::iterator it, int u) {

	REP(i, G[u].size()) {
		PII *v = &G[u][i];
		if(v->second) {
			v->second = 0;
			REP(j, G[v->first].size()) {
				PII *vu = &G[v->first][j];
				if(vu->first == u && vu->second) {
					vu->second = 0; break;
				}
			}
			eulerPath(path.insert(it, u), v->first);
		}
	}
}

void printGraph() {
	REP(i, G.size()) {
		printf("Node #%d : ", i+1);
		REP(j, G[i].size()) printf("(%d %d) ", G[i][j].first+1, G[i][j].second);
		printf("\n");
	}
	exit(-1);
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	freopen("Input_TheNecklace.txt", "r", stdin);
#endif
	int T; scanf("%d", &T);
	int graphSize = 50;
	int edges, u, v;

	int sourceVertex = 0;
	REP(test, T) {
		// init
		G = VVPII(graphSize);
		scanf("%d", &edges);
		REP(edge, edges) scanf("%d%d", &u, &v), 
			--u, --v, G[u].pb(mp(v,1)), G[v].pb(mp(u,1)), sourceVertex = u;
		//printGraph();

		printf("Case #%d\n", test+1);
		if(isEulerian()) {
			path.clear();
			eulerPath(path.begin(), sourceVertex);
			VI tempPath(path.begin(), path.end());
			REP(i, tempPath.size()-1)
				printf("%d %d\n", tempPath[i]+1, tempPath[i+1]+1);
			if(tempPath.size() > 0)
				printf("%d %d\n", tempPath[tempPath.size()-1]+1, tempPath[0]+1);
		}
		else printf("some beads may be lost\n");
		
		if(test != T-1) printf("\n");
	}
}
