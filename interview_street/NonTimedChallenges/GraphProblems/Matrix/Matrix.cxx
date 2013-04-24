// the solution is based on the fact that the given graph is a tree. So, there
// are no cycles. Let us pick a random city as the root of this tree. Using 
// using this root, we'll construct a parent array using bfs that will lead
// all nodes to the root. Now, we start with a node where a machine is located.
// Now we start a walk to the parent keeping track of the smallest edge; if 
// we reach a machine on the way we stop and cut the smallest edge and move
// to the next node and start the walk. If we reach a node that has more than
// 2 edges i.e. it probably has one more branch and the branch that we don't 
// walk to might have a machine. Because of this, we stop here and add this
// node to the queue. We use a priority queue based on the distance of the 
// node from the root; this enables us to walk the farthest machine nodes first,
// so that, any node with more than 2 edges can be delt with before those nodes,
// start walking again.

// I'm really hopeless at explaining, check the code for details.

#include <cstdio>
#include <cstdlib>
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
#define INF 10000000000

int main(int argc, char *argv[])
{
	int N, K;

	scanf(" %d %d", &N, &K);

	VVIL G(N);
	int u, v;  vlong w;
	REP(edge, N-1) {
		scanf(" %d %d %llu", &u, &v, &w); 
		G[u].pb(mp(v,w));
		G[v].pb(mp(u,w));
	}



	VI parents(N, -1);
	VL weights(N, INF);
	VI dist(N, -1);
	u = rand()%N;

	QI Q; Q.push(u);
	parents[u] = u;
	weights[u] = INF;
	dist[u] = 0;
	while(!Q.empty()) {
		u = Q.front(); Q.pop();
		REP(j, G[u].size()) {
			v = G[u][j].first;
			w = G[u][j].second;
			if(parents[v] == -1) {
				Q.push(v); parents[v] = u; weights[v] = w; dist[v] = dist[u]+1;
			}
		}
	}
//	REP(i, weights.size()) fprintf(stderr, "%llu ", weights[i]);
//	fprintf(stderr, "\n");
	VI machines(N, 0);
	priority_queue<II> mQ; //machine q
	REP(m, K) { scanf(" %d", &u); machines[u] = 1; mQ.push(mp(dist[u], u)); }

	vlong res = 0;
	VL minWeightVert(N, INF);
	while(!mQ.empty()) {
		u = mQ.top().second; mQ.pop();
		int p = parents[u];

//		fprintf(stderr, "%d -> ", u);
		while(p != u) {
//			fprintf(stderr, "%d ->", p);
			vlong minWeight = min(minWeightVert[u], weights[u]);

			// reached another machine
			if(machines[p]) {
				res += minWeight; 
				break;
			}

			if(G[p].size() > 2 && minWeightVert[p] == INF) {
				minWeightVert[p] = minWeight; 
				mQ.push(mp(dist[p], p));
				break;
			}

			if(minWeightVert[p] != INF) {
				if(minWeight > minWeightVert[p]) {
					res += minWeightVert[p];
					minWeightVert[p] = minWeight;
				}
				else {
					res += minWeight;
				}
				break;
			}
			
			minWeightVert[p] = minWeight;

			u = p;
			p = parents[u];
		}
//		fprintf(stderr, "RES: %llu\n", res);
	}

	printf("%llu\n", res);
	return 0;
}
