#include <cstdio>
#include <vector>
#include <map>
#include <string>
#include <utility>
#include <algorithm>
#include <stack>
#include <iostream>

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
			//if(v == curNode) printf("%s\n", nodeToNameMap[v].c_str());
			//else printf("%s, ", nodeToNameMap[v].c_str());
			singleSSC.push_back(v);
		}while(v != curNode);
		ssc.push_back(singleSSC);
	}
}

int main(int argc, char *argv[]) 
{
	int n, m;
	int dataSet = 1;
	while(scanf(" %d %d", &n, &m) != EOF && n != 0 && m != 0)
	{
		if(dataSet > 1) printf("\n");
		G = VVI(n); dfsNum = VI(n); dfsLow = VI(n); dfsVisited = VI(n, -1);
		st = stack<int>();
		ssc.clear();
		nameToNodeMap.clear();
		nodeToNameMap = vector<string>(n);
		curNum = 0; // i will use this first to number the names and then reset
		string name1, name2;
		char name[1000];
		for(int i = 0; i < m; i++) {
			scanf(" %s", name);
			name1 = string(name);
			scanf(" %s", name);
			name2 = string(name);
			
			if(nameToNodeMap.find(name1) == nameToNodeMap.end()) {
				nameToNodeMap[name1] = curNum;
				nodeToNameMap[curNum++] = name1;
			}
			if(nameToNodeMap.find(name2) == nameToNodeMap.end()) {
				nameToNodeMap[name2] = curNum;
				nodeToNameMap[curNum++] = name2;
			}
			G[nameToNodeMap.find(name1)->second].push_back(
				nameToNodeMap.find(name2)->second);
		}
		curNum = 0;

			
			
		printf("Calling circles for data set %d:\n", dataSet++);
		for(int i = 0; i < n; i++)
			if(dfsVisited[i] < 0)
				dfsSSC(i);

		for(VVI::reverse_iterator it = ssc.rbegin(); it != ssc.rend(); ++it)
		{
			for(VI::reverse_iterator it_entry = it->rbegin();
				it_entry != it->rend(); ++it_entry)
			{
				if((it_entry + 1) != it->rend())
					printf("%s, ", nodeToNameMap[*it_entry].c_str());
				else
					printf("%s\n", nodeToNameMap[*it_entry].c_str());
			}
		}

	}
	return 0;
}
