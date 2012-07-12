// This problem is solvable in O(ElogV)
// Check the paper, http://www.eecs.harvard.edu/~parkes/cs286r/spring02/papers/vickrey.pdf
// Paper is easy to read and algo looks simple.

#include <stack>
#include <queue>
#include <vector>
#include <cstdio>
#include <utility>
#include <functional>
#include <algorithm>
#include <iterator>
#include <iostream>

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef pair<int,int> PII;
typedef pair<int,PII> PIPII;
typedef vector<PII> VPII;
typedef vector<VPII> VVPII;
typedef vector<PIPII> VPIPII;
typedef priority_queue<PII, VPII, greater<PII> > PQPII;
typedef priority_queue<int, VI, greater<int> > PQI;
typedef priority_queue<PIPII, VPIPII, greater<PIPII> > PQPIPII;

#define REP(i, n) for(int i = 0; i < (n); ++i)
#define FOR(i, st, n) for(int i = (st); i < (n); ++i)
#define mp make_pair

void errPrint(const VI &vec)
{
	//copy(vec.begin(), vec.end(), ostream_iterator<int>(cerr, " "));
	//cerr << endl;
}

// Path will contain backtracking path from all vertices to source
// Distance will contain shortest distance to all vertices
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
					path[v] = u.second;
				}
			}
		}
	}
}


// Identify the path itself
void pathFromStoD(const int source, 
				  const int _dest, 
				  const VI &backtrack,
				  VI &StoD, // this will only contain the vertices that belong to the path
				  VI &StoD2) // this will contain all vertices but marker for vertices that belong to the path
{
	int dest = _dest;
	stack<int> st;
	StoD.clear();
	StoD2 = VI(backtrack.size(), -1);
	while(backtrack[dest] != -1 ) {
		st.push(dest);
		if(dest == source) break;
		dest = backtrack[dest];
	}
	
	while(!st.empty()) {
		StoD.push_back(st.top());
		StoD2[st.top()] = backtrack[st.top()];
		st.pop();
	}
}

// Identify the path index a vertex belongs to.
void identifyPathIndex(const VI &path, 
					   const VI &backtrack, 
					   VI &pathIndex)
{
	pathIndex = VI(backtrack.size(), -1);
	REP(i, path.size()) pathIndex[path[i]] = i;

	REP(i, pathIndex.size()) {
		int bt = i;
		if(backtrack[bt] == -1)
			pathIndex[i] == -1;
		else {
			stack<int> st;
			while(pathIndex[bt] == -1 && bt != backtrack[bt]) {
				st.push(bt);
				bt = backtrack[bt];
			}
//			if(bt == backtrack[bt])
//				pathIndex[i] = bt;
//			else
			pathIndex[i] = pathIndex[bt];
			while(!st.empty()) {
				pathIndex[st.top()] = pathIndex[i];
				st.pop();
			}
		}
	}
}

// Prepare mincut edges for each vertex
void prepareMinCuts(const VVPII &G, 
					const VI &pathIndex,
					const VI &path,
					vector<VPIPII> &mincut)
{
	mincut = vector<VPIPII>(path.size());

	// For all edges check which mincut they belong to and assign it to that
	REP(u, G.size()) {
		REP(i, G[u].size()) {
			int v = G[u][i].first; 
			int w = G[u][i].second; // (u,v) with weight (w) makes the edge

			if(pathIndex[u] != -1 && pathIndex[u] < pathIndex[v]
			   && (pathIndex[u] != pathIndex[v] - 1  || 
				   (path[pathIndex[u]] != u || path[pathIndex[v]] != v )))
				mincut[pathIndex[u]].push_back(mp(w, mp(u,v)));
		}
	}
}

// Create a cache to identify the minimum path length from source -> destination
// when an edge from the shortest path is removed.
void prepareCache(const int source,
				  const int destination,
				  const VI &distToSource,
				  const VI &distToDestination,
				  const vector<VPIPII> &mincutEdges,
				  const VI &pathIndex,
				  VI &shortestPath)
{
	shortestPath = VI(mincutEdges.size(), -1);
	PQPII pq;
	REP(i, shortestPath.size()) {
		REP(j, mincutEdges[i].size()) {
			int w = mincutEdges[i][j].first;
			int u = mincutEdges[i][j].second.first;
			int v = mincutEdges[i][j].second.second;

			if(distToSource[u] != -1 && distToDestination[v] != -1) {
				w = w + distToSource[u] + distToDestination[v];
				pq.push(mp(w,v));
			}
		}

		while(!pq.empty() && pathIndex[pq.top().second] >= 0 && 
			  pathIndex[pq.top().second] <= i) 
			pq.pop();
		if(!pq.empty())
			shortestPath[i] = pq.top().first;
	}
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

	VI distToSource, distToDestination;
	VI pathFromSource, pathFromDestination;
	fprintf(stderr, "Dijkstras from source.\n");
	dijkstraSSSP(G, source, distToSource, pathFromSource);
	fprintf(stderr, "Dijkstras from destination.\n");
	dijkstraSSSP(G, destination, distToDestination, pathFromDestination);
	fprintf(stderr, "Distance to source: ");
	errPrint(distToSource);
	fprintf(stderr, "Path from source: ");
	errPrint(pathFromSource);
	fprintf(stderr, "Distance to destination: ");
	errPrint(distToDestination);
	fprintf(stderr, "Path from destination: ");
	errPrint(pathFromDestination);


	VI shortestPath, spBacktrack;
	fprintf(stderr, "Construct path from source to destination.\n");
	pathFromStoD(source, destination, pathFromSource, 
				 shortestPath, spBacktrack);
	fprintf(stderr, "Shortest path: ");
	errPrint(shortestPath);
	fprintf(stderr, "Shortest path backtrack: ");
	errPrint(spBacktrack);

	VI pathIndex;
	fprintf(stderr, "Identify path index for each vertex.\n");
	identifyPathIndex(shortestPath, pathFromSource, pathIndex);
	fprintf(stderr, "Path Index: ");
	errPrint(pathIndex);


	vector<VPIPII> mincut;
	fprintf(stderr, "Find mincuts.\n");
	prepareMinCuts(G, pathIndex, shortestPath, mincut);
	VI cacheShortestPath;
	fprintf(stderr, "Prepare cache for shortest path\n");
	prepareCache(source, destination, distToSource, distToDestination,
				 mincut, pathIndex, cacheShortestPath);

	fprintf(stderr, "Cache shortest path: ");
	errPrint(cacheShortestPath);
	
	int numOfQueries;
	scanf(" %d", &numOfQueries);
	REP(edge, numOfQueries) {
		scanf(" %d %d", &u, &v);

		if(pathFromSource[u] == v) swap(u,v);

		if(pathFromSource[v] == u && 
		   shortestPath[pathIndex[u]] == u &&
		   shortestPath[pathIndex[v]] == v) {
			if(cacheShortestPath[pathIndex[u]] == -1) 
				printf("Infinity\n");
			else
				printf("%d\n", cacheShortestPath[pathIndex[u]]);
		}
		else if(distToSource[destination] == -1)
			printf("Infinity\n");
		else
			printf("%d\n", distToSource[destination]);
	}

	return 0;
}
