#include <stack>
#include <vector>
#include <queue>
#include <cstdio>
#include <cstring>
#include <utility>
#include <string>
#include <cassert>

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef pair<int, int> II;
typedef vector<II> VII;
typedef vector<VII> VVII;
typedef vector<string> VS;
typedef queue<II> QII;

#define mp make_pair
#define REP(i, n) for(int i = (n); i < (n); i++)

int setBit(int n, int bitIndex) {
	return ((1 << (bitIndex-1)) | n);
}

int unsetBit(int n, int bitIndex) {
	return (~(1 << (bitIndex-1))) & n;
}

bool isBitSet(int n, int bitIndex) {
	return ((1 << (bitIndex-1)) & n) != 0;
}

int flipBit(int n, int bitIndex) {
	return isBitSet(n, bitIndex) ? 
		unsetBit(n, bitIndex) : setBit(n, bitIndex);
}

void bitFuncsUnitTest() {
	assert(unsetBit(2, 2) == 0);
	assert(unsetBit(8, 16) == 8);
	assert(setBit(0, 4) == 8);
	assert(setBit(16, 5) == 16);
	assert(isBitSet(32, 6) == true);
	assert(isBitSet(16, 6) == false);
}

void backtrackPrint(const VVII &backtrack,
					const vector<VS> &btText,
					const int curVertex,
					const int curLight,
					stack<string> &output)
{
	II next = backtrack[curVertex][curLight];
	for(int nextVertex = next.first, nextLight = next.second;
		curVertex != nextVertex || curLight != nextLight; 
		next = backtrack[nextVertex][nextLight],
			nextVertex = next.first, nextLight = next.second)
		output.push(btText[nextVertex][nextLight]);
}

void bfs(const VVI &G, const VVI &lightG) {
	int source = 0; 
	int destVert = G.size()-1;
	int destLight = 1<<(G.size()-1);

	VVII backtrack(G.size(), VII( (1<<G.size())-1, mp(-1,-1) ));
	vector<VS> btText(G.size(), VS((1<<G.size()) - 1));

	QII Q;
	char text[100];
	backtrack[source][1] = mp(0,1);
	Q.push(mp(0,1));
	while(!Q.empty()) {
		II curState = Q.front();
		int curVert = curState.first;
		int curLight = curState.second;
		Q.pop();

		if(curVert == destVert && curLight == destLight) {
			stack<string> output;
			backtrackPrint(backtrack, btText, curVert, curLight, output);
			printf("The problem can be solved in %d steps:\n", 
				   (int)output.size());
			while(!output.empty()) {
				string op = output.top();
				output.pop();
				printf("- %s\n", op.c_str());
			}
			return;
		}

		// first, get into any nodes that are accessible
		REP(i, G[curVert].size()) {
			int nextVert = G[curVert][i];
			if(backtrack[nextVert][curLight].first == -1) {

				Q.push(mp(nextVert, curLight));
				backtrack[nextVert][curLight] = mp(curVert, curLight);

				sprintf(text, "Move to room %d.", nextVert+1);
				btText[nextVert][curLight] = string(text);
			}
		}

		// Second, flip any lights accessible
		REP(i, lightG[curVert].size()) {
			int nextVert = lightG[curVert][i];
			int nextLight;
			if(isBitSet(curLight, nextVert)) {
				nextLight = setBit(curLight, nextVert);
				sprintf(text, "Switch on light in room %d", nextVert+1);
			}
			else {
				nextLight = unsetBit(curLight, nextLight);
				sprintf(text, "Switch off light in room %d", nextVert+1);
			}

			if(backtrack[curVert][nextLight].first == -1) {
				Q.push(mp(curVert, nextLight));
				backtrack[curVert][nextLight] = mp(curVert, curLight);
				btText[curVert][nextLight] = string(text);
			}
		}
	}
}

int main(int argc, char *argv[])
{

	return 0;
}
