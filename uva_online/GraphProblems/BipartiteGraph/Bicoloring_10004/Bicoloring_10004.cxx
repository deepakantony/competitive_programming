#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

#define NOCOLOR 0
#define WHITE 1
#define BLACK 2

using namespace std;
typedef vector<int> VI;
typedef vector<VI> VVI;

VVI G;
VI colors;

bool dfs(int curNode, int prevColor) {
	if(prevColor == colors[curNode])
		return false;

	if(colors[curNode] != NOCOLOR)
		return true;

	colors[curNode] = prevColor == WHITE ? BLACK:WHITE;
	for(int i = 0; i < G[curNode].size(); i++)
		if(!dfs(G[curNode][i], colors[curNode]))
			return false;

	return true;
}

int main(int argc, char *argv[])
{
	int graphSize;
	
	while(scanf(" %d", &graphSize), graphSize != 0){
		G  = VVI(graphSize);
		colors = VI(graphSize, 0);
		int nEdges, node1, node2;
		scanf(" %d", &nEdges);
		while(nEdges--) {
			scanf(" %d %d", &node1, &node2);
			G[node1].push_back(node2);
			G[node2].push_back(node1);
		}
		if(dfs(0, BLACK))
			printf("BICOLORABLE.\n");
		else printf("NOT BICOLORABLE.\n");
	}
	return 0;
}
