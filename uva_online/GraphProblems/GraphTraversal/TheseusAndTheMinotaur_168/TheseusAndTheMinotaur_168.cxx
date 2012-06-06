#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <cstdio>
#include <cstring>
#include <utility>
#include <cctype>

using namespace std;

typedef vector<int> VI;
typedef vector< VI > AdjList;

void printVec(VI vec) {
	for(VI::const_iterator it = vec.begin();
		it != vec.end(); ++it)
		printf("%d ", *it);
	printf("\n");
}

void initGraph(AdjList &G, string input)
{
	G = AdjList(26);

	for(string::const_iterator it = input.begin();
		it != input.end(); ++it)
	{
		int curNode = -1;
		while(it != input.end() && isalpha(*it)) {
			curNode = (*it) - 'A';
			it++;
		}

		if(it == input.end() || (*it) != ':' || curNode == -1) break;
		else it++;

		while(it != input.end() && isalpha(*it)) {
			G[curNode].push_back(int((*it)-'A'));
			it++;
		}
		
		if(it == input.end() || (*it) != ';') break;
	}
}

bool next(VI graphList, int curNode, int prevNode, int *lights, int &result)
{
	for(VI::const_iterator it = graphList.begin();
		it != graphList.end(); ++it) {
		if(lights[*it] == 0 && (*it) != prevNode) {
			result = *it;
			return true;
		}
	}

	result = -1;
	return false;
}

int trapMinotaur(const AdjList &G, int minotaur, int theseus, int k)
{
	int nextPos;
	int curMove = 0;
	int lights[26];
	memset(lights, 0, sizeof lights);
	while(next(G[minotaur], minotaur, theseus, lights, nextPos)) {
		curMove++;
		theseus = minotaur;
		minotaur = nextPos;
		if(curMove == k) {
			lights[theseus] = 1;
			curMove = 0;
			printf("%c ", 'A' + char(theseus));
		}
	}
	printf("/%c\n", 'A' + minotaur);
}

int main(int argc, char *argv[])
{
	char inputString[5000];
	scanf(" %s", inputString);
	char minotaur, theseus;
	int k;

	while(inputString[0] != '#') {
		AdjList G;
		initGraph(G, string(inputString));

		scanf(" %c %c %d", &minotaur, &theseus, &k);

		trapMinotaur(G, minotaur-'A', theseus-'A', k);

		scanf(" %s", inputString);
	}
}
