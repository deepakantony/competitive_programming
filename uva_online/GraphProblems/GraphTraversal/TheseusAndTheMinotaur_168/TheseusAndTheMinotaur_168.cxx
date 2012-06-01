#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <cstdio>
#include <cstring>
#include <utility>

using namespace std;

typedef vector<int> VI;
typedef vector< VI > AdjList;

void initGraph(AdjList &G, string input)
{

}

int main(int argc, char *argv[])
{
	char inputString[5000];
	scanf(" %s", inputString);
	while(inputString[0] != '#') {
		AdjList G;
		initGraph(G, string(inputString));
		scanf(" %s", inputString);
	}
}
