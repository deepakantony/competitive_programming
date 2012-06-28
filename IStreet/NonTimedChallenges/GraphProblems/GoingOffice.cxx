// This problem is solvable in O(ElogV)
// Check the paper, http://www.eecs.harvard.edu/~parkes/cs286r/spring02/papers/vickrey.pdf
// Paper is easy to read and algo looks simple.

#include <queue>
#include <vector>
#include <cstdio>
#include <utility>
#include <functional>

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef pair<int,int> PII;
typedef pair<int,PII> PIPII;
typedef vector<PII> VPII;
typedef vector<VPII> VVPII;
typedef priority_queue<PII, VI, greater<int> > PQPII;
typedef priority_queue<int, VI, greater<int> > PQI;
typedef priority_queue<PIPII, VI, greater<int> > PQPIPII;

#define REP(i, n) for(int i = 0; i < (n); ++i)
#define FOR(i, st, n) for(int i = (st); i < (n); ++i)
#define mp make_pair


void dijkstraSSSP(const VVPII &G,  // adj list
				  const int source,
				  VI &distance,
				  VI &path)
{
	distance = VI(G.size(), -1);
	path = VI(G.size(), -1);
	distance[source] = 0;
	path[source] = source;
	PQPII pq; pq.push(mp(0, source));

	while(!pq.empty()) {
		PII u = pq.top(); pq.pop();
		
		if(u.first == distance[u.second]) {
			REP(i, G[u.second].size()) {
				int v = G[u.second][i].first;
				int w = G[u.second][i].second;
				if( distance[v] == -1 || (w + u.first) < distance[v]) {
					distance[v] = w + u.first;
					pq.push(mp(distance[v], v));
				}
			}
		}
	}
}


void unitTests()
{

}


int main(int argc, char *argv[])
{
	VVPII G;
	int numOfVerts, numOfEdges;
	scanf(" %d %d", &numOfVerts, &numOfEdges);

	G = VVPII(numOfVerts);
	int u, v, w;
	REP(edge, numOfEdges) {
		scanf(" %d %d %d", &u, &v, &w);
		G[u].push_back(mp(v,w));
		G[v].push_back(mp(u,w));
	}

	int source, destination;
	scanf(" %d %d", &source, &destination);
	
	int numOfQueries;
	scanf(" %d", &numOfQueries);
	REP(edge, numOfQueries) {
		scanf(" %d %d", &u, &v);
	}

	return 0;
}
