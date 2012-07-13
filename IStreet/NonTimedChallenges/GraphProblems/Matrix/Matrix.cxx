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

	VI machines(N, 0);
	QI mQ; //machine q
	REP(m, K) { scanf(" %d", &u); machines[u] = 1; mQ.push(u); }


	VI parents(N, -1);
	VL weights(N, INF);
	u = rand()%N;

	QI Q; Q.push(u);
	parents[u] = u;
	weights[u] = INF;
	while(!Q.empty()) {
		u = Q.front(); Q.pop();
		REP(j, G[u].size()) {
			v = G[u][j].first;
			w = G[u][j].second;
			if(parents[v] == -1) {
				Q.push(v); parents[v] = u; weights[v] = w;
			}
		}
	}
//	REP(i, weights.size()) fprintf(stderr, "%llu ", weights[i]);
//	fprintf(stderr, "\n");


	vlong res = 0;
	VL minWeightVert(N, INF);
	while(!mQ.empty()) {
		u = mQ.front(); mQ.pop();
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
				mQ.push(p);
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
