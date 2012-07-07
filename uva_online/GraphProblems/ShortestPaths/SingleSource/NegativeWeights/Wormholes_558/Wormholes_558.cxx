#include <vector>
#include <cstdio>
#include <utility>

using namespace std;

#define REP(i,n) for(int i = 0; i < (n); i++)
#define mp make_pair
#define INF 1000000000

typedef pair<int,int> II;
typedef pair<int, II> III;
typedef vector<int> VI;
typedef vector<II> VII;
typedef vector<III> VIII;

bool doesNegativeLoopExist(int numOfVertices, const VIII &edgelist) {
	VI dist(numOfVertices, INF);
	dist[0] = 0;
	REP(vert, numOfVertices) REP(edge, edgelist.size()) {
		int u = edgelist[edge].second.first;
		int v = edgelist[edge].second.second;
		int t = edgelist[edge].first;
		dist[v] = min(dist[v], dist[u]+t);
	}
	bool res = false;
	REP(edge,edgelist.size()) {
		int u = edgelist[edge].second.first;
		int v = edgelist[edge].second.second;
		int t = edgelist[edge].first;
		if((dist[u]+t) < dist[v]) { res = true; break; }
	}
	return res;
}

int main(int argc, char *argv[])
{
	int numOfTests; scanf(" %d", &numOfTests);
	int numOfVerts, numOfEdges;
	int u,v,t;
	while(numOfTests--) {
		scanf(" %d %d", &numOfVerts, &numOfEdges);
		VIII edgelist;
		REP(edge, numOfEdges) {
			scanf(" %d %d %d", &u, &v, &t);
			edgelist.push_back(mp(t, mp(u,v)));
		}
		if(doesNegativeLoopExist(numOfVerts, edgelist))
			printf("possible\n");
		else printf("not possible\n");
	}
	return 0;
}
