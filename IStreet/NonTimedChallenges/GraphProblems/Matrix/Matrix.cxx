#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>

using namespace std;

typedef unsigned long long vlong;
typedef vector<int> VI;
typedef vector<vlong> VL;
typedef vector<VL> VVL;
typedef pair<int, vlong> IL;
typedef pair<int, int> II;
typedef pair<vlong, II> LII;
typedef vector<LII> VLII;
typedef vector<IL> VIL;
typedef vector<VIL> VVIL;
typedef queue<int> QI;

#define REP(i, n) for(int i = 0; i < (n); ++i)
#define FOR(i, s, n) for(int i = (s); i < (n); ++i)
#define pb push_back
#define mp make_pair
#define INF 1000000000

int main(int argc, char *argv[])
{
	int N, K;

	scanf(" %d %d", &N, &K);

	VVIL G(N);
	int u, v;  vlong w;
	REP(edge, N-1) 
		scanf(" %d %d %d", &u, &v, &w), G[u].pb(mp(v,w)), G[v].pb(mp(u,w));

	VI parents(N, -1);
	VL weights(N, INF);
	QI Q; Q.push(0); 
	parents[0] = 0;
	weights[0] = INF;
	while(!Q.empty()) {
		u = Q.front(); Q.pop();
		REP(j, G[u].size()) {
			v = G[u][v].first;
			w = G[u][v].second;
			if(parents[v] == -1)
				Q.push(v), parents[v] = u, weights[v] = w;
		}
	}

	VI machines(N, 0);
	REP(machine, K) scanf(" %d", &u), machines[machine] = 1;

	vlong timeReq = 0;
	VL minTimeVert(N, INF);
	VI minTimeEdge(N, -1);
	REP(k, N) if(machine[k]) {
		// now trace back till the root or a node with time updated.

		int curVert = k;
		minTimeEdge[curVert] = curVert;
		minTimeVert[curVert] = weights[curVert];
		while(curVert != parents[curVert]) {
			int p = parents[curVert];

			// reached a machine; remove the shortest edge
			if(machines[p]) {
				int updateVertex = minTimeEdge[curVert];
				timeReq += minTimeVert[curVert];
				parents[updateVertex] = updateVertex;
				weights[updateVertex] = INF;
				break;
			}

			// reached a visited vertex; remove the shorter of the two edges
			if(minTimeVert[p] != INF) {
				if(minTimeVert[p] > minTimeVert[curVert]) {
					int updateVertex = minTimeEdge[curVert];
					timeReq += minTimeVert[curVert];
					parents[updateVertex] = updateVertex;
					weights[updateVertex] = INF;
				}
				else {
					
				}
			}
			
			if(minTimeVert[curVert] > weights[p]) {
				minTimeVert[p] = weights[p];
				minTimeEdge[p] = minTimeEdge[curVert];
			}
			else {
				minTimeVert[p] = minTimeVert[curVert];
				minTimeEdge[p] = minTimeEdge[curVert];
			}

			curVert = p;
		}
	}

	return 0;
}
