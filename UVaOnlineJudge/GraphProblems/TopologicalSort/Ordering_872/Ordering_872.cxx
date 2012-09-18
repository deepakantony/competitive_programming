#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <deque>

#define FOR(i, st, nd) for(int (i) = (st); (i) < (nd); (i)++)
#define REP(i, n) for(int (i) = 0; (i) < (n); (i)++)

using namespace std;

typedef vector<char> VC;
typedef vector<int> VI; 
typedef vector<VI> VVI;
typedef vector<string> VS;
typedef deque<int> QI;

VVI G; // The Graph
VVI reverseG; // The reverse graph - technically this is the actual one
VC nodeG; // node value of the graph
VI countG; // count of dependencies for each node

bool allTopSort(QI &q, VS &res, string &currentRes) {
	// backtracking
	// read the algo by Dr Knuth on generating all topological sort
	//printf("%s\n", currentRes.c_str());
	// terminating conditions
	if(q.empty()) return false;
	// psuedo cycle verification
	int alreadyPrinted = (currentRes.size()+1)/2;
	if((alreadyPrinted+q.size()) > G.size())
		return false;
	// is this the last element in the Queue and is it the last 
	if(q.size() == 1 && G[q.front()].size() == 0){
		if( (alreadyPrinted+1) == G.size())
		{
			res.push_back(currentRes + nodeG[q.front()]);
			return true;
		}
		else return false;
	}

	int base = q.front();
	do {
		int cur = q.front();
		q.pop_front();
		currentRes = currentRes + nodeG[cur] + " ";

		// remove all 'cur' dependent nodes 
		REP(index, G[cur].size()) {
			--countG[G[cur][index]];
			if(countG[G[cur][index]] == 0)
				q.push_back(G[cur][index]);
		}

		if(!allTopSort(q, res, currentRes)) return false;

		// add all 'cur' dependent nodes
		REP(index, G[cur].size()) {
			if(countG[G[cur][index]] == 0)
				q.pop_back();
			countG[G[cur][index]]++;
		}
		currentRes.erase(currentRes.size()-2, currentRes.size());

		q.push_back(cur);
	} while(q.front() != base);
	return true;
}

QI buildQ() {
	QI res;
	REP(index, countG.size())
		if(!countG[index])
			res.push_back(index);
	return res;
}

void buildCountG() {
	countG = VI(reverseG.size(), 0);
	REP(index, reverseG.size())
		countG[index] = reverseG[index].size();
}

void printTopSorts(VS &topSorts) {
	sort(topSorts.begin(), topSorts.end());
	REP(index, topSorts.size())
		printf("%s\n", topSorts[index].c_str());
}

int main(int argc, char *argv[])
{
	int nTests;
	scanf("%d", &nTests);
	int nodeToNumberMap[26];
	char input[1000];
	while(nTests--) {
		scanf(" %[^\n]s", input);
		int graphSize = (strlen(input)+1)/2;
		nodeG = VC(graphSize);
		REP(index, graphSize) {
			sscanf(input+index*2, " %c", &nodeG[index]);
			nodeToNumberMap[nodeG[index]-'A'] = index;
		}
		scanf(" %[^\n]s", input);
		char A, rel, B;
		G = VVI(graphSize);
		reverseG = VVI(graphSize);
		
		int relSize = (strlen(input)+1)/4;
		REP(index, relSize) {
			sscanf(input+index*4, " %c%c%c", &A, &rel, &B);
			G[nodeToNumberMap[A-'A']].push_back(nodeToNumberMap[B-'A']);
			reverseG[nodeToNumberMap[B-'A']].push_back(nodeToNumberMap[A-'A']);
		}

		buildCountG();

		QI Q = buildQ();
		VS res;
		string curRes = "";
		if(Q.empty() || !allTopSort(Q, res, curRes))
			printf("NO\n");
		else
			printTopSorts(res);

		if(nTests != 0) printf("\n");
	}

	return 0;
}
