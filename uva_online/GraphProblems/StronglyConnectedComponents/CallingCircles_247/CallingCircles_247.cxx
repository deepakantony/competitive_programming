#include <cstdio>
#include <vector>
#include <map>
#include <string>
#include <utility>
#include <algorithm>
#include <stack>

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;

VVI G;
VI dfsNum, dfsLow, dfsVisited;
VVI ssc; // final result; strongly connected components
int curNum;
map<string, int> nameToNodeMap;
vector<string> nodeToNameMap;
stack<int> st;

void dfsSSC(int curNode)
{
	dfsLow[curNode] = dfsNum[curNode] = curNum++;
	dfsVisited[curNode] = 1;
	st.push(curNode);
	for(int i = 0; i < G[curNode].size(); i++)
	{
		int v = G[curNode][i];
		if(dfsVisited[v] < 0) 
			dfsSSC(v);
		if(dfsVisited[v] > 0) 
			dfsLow[curNode] = min(dfsLow[curNode], dfsLow[v]);
	}

	if(dfsLow[curNode] == dfsNum[curNode])
	{
		VI singleSSC;
		int v;
		do {
			v = st.top();
			st.pop();
			dfsVisited[v] = 0;
			singleSSC.push_back(v);
		}while(v != curNode);
		ssc.push_back(singleSSC);
	}
}

int maint(int argc, char *argv[]) 
{
	return 0;
}
