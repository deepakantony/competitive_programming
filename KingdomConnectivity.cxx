// Kingdom Connectivity(20 points)
// 
// It has been a prosperous year for King Charles and he is rapidly expanding 
// his kingdom.A beautiful new kingdom has been recently constructed and in 
// this kingdom there are many cities connected by a number of one-way roads.
// Two cities may be directly connected by more than one roads, this is to 
// ensure high connectivity.
// 
// In this new kingdom King Charles has made one of the cities at his financial 
// capital and one as warfare capital and he wants high connectivity between 
// these two capitals.The connectivity of a pair of cities say city A and city 
// B is defined as the number of different paths from city A to city B. A path 
// may use a road more than once if possible. Two paths are considered different 
// if they do not use exactly the same sequence of roads.
// 
// There are N cities numbered 1 to N in the new kingdom and M one-way roads  . 
// City 1 is the monetary capital and city N is the warfare capital.
// 
// You being one of the best programmers in new kingdom need to answer the 
// connectivity of financial capital and warfare capital ,i.e number of 
// different paths from city 1 to city N.
// 
// Input Description:
// 
// First line contains two integers N and M.
// 
// Then follow M lines ,each having two integers say x and y, 1<=x,y<=N , 
// indicating there is a road from city x to city y.
// 
// Output Description:
// 
// Print the number of different paths from city 1 to city N modulo 
// 1,000,000,000(10^9).If there are infinitely many different paths print 
// "INFINITE PATHS"(quotes are for clarity).
// 
// Sample Input:
// 
// 5 5
// 1 2
// 2 4
// 2 3
// 3 4
// 4 5
// 
// Sample Output:
// 
// 2
// 
// Sample Input:
// 
// 5 5
// 1 2
// 4 2
// 2 3
// 3 4
// 4 5
// 
// Sample Output:
// 
// INFINITE PATHS
// 
// Constraints:
// 
// 2<=N<=10,000(10^4)
// 
// 1<=M<=1,00,000(10^5) 

// Solution for this problem is fairly simple. Think topological sort, but
// we need to find number of topological orders. So, we'll start from the sink
// and do a DFS to find the source. You could start from the source, but starting
// at sink seemed right at the time. Easily solved by recursive solution; take
// care to handle loop at the source itself and loops that will never reach
// the sink.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define INFINITE -1
#define MODULO_NUM 1000000000ll

struct GraphVertex
{
	GraphVertex() : partOfCycle(false), distance(0ll), distanceCalculated(false) {}
	void addEdge(int v) { inEdges.push_back(v); }
	vector<int>::iterator begin() { return inEdges.begin(); }
	vector<int>::iterator end() { return inEdges.end(); }
	bool partOfCycle;
	vector<int> inEdges;
	bool distanceCalculated;
	long long distance;
};

void totalNumberOfPaths(int curVertex, vector<GraphVertex> &G,
						vector<char> &currentPath)
{
	for(auto inEdge = G[curVertex].begin(); 
		inEdge != G[curVertex].end(); ++inEdge)
	{
		// first check if we would enter a cycle
		if(currentPath[*inEdge])
		{
			G[curVertex].partOfCycle = G[*inEdge].partOfCycle = true;
			continue;
		}
		
		// not a cycle, so continue
		currentPath[*inEdge] = 1;
		if(!G[*inEdge].distanceCalculated)
		{
			totalNumberOfPaths(*inEdge, G, currentPath);
		}
		if(*inEdge == 0) // reached the source vertex
		{
			G[0].distance = G[0].partOfCycle ? INFINITE : 1ll;
		}

		if(G[*inEdge].distance == INFINITE)
		{
			G[curVertex].distance = INFINITE;
			break;
		}
		G[curVertex].distance = (G[curVertex].distance + 
								 G[*inEdge].distance) % MODULO_NUM;
		currentPath[*inEdge] = 0;
	}
	if(G[curVertex].partOfCycle && G[curVertex].distance != 0)
		G[curVertex].distance = INFINITE;
	G[curVertex].distanceCalculated = true;
}

long long totalNumberOfPaths(int endV, vector<GraphVertex> &G)
{
	vector<char> inCurrentPath(G.size());
	fill(inCurrentPath.begin(), inCurrentPath.end(), 0);

	inCurrentPath[endV] = 1;

	totalNumberOfPaths(endV, G, inCurrentPath);
	return G[endV].distance;
}

void solveKingdomConnectivity()
{
	int cities, roads; // vertices and 
	cin >> cities >> roads;

	vector<GraphVertex> graph(cities);
	for(int road = 0; road < roads; ++road)
	{
		int city1, city2;
		cin >> city1 >> city2;
		graph[city2-1].addEdge(city1-1);
	}
	long long res = totalNumberOfPaths(cities-1, graph);
	if(res == INFINITE)
		cout << "INFINITE PATHS" << endl;
	else
		cout << res << endl;
}

void unitTests()
{
//	vector<GraphVertex> graph(5);
	//graph[0].ad
}

int main(int argc, char *argv[])
{
	solveKingdomConnectivity();
}
