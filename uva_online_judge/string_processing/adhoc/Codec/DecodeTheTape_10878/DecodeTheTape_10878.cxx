/*
  Problem: Decode the tape.
  Link: http://uva.onlinejudge.org/external/108/10878.html
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: The encoding in the tape is just ascii binary. When decoding ignore
  '|' and '.' and use 'o' as 1's in an 8 bit char. So the ' o     o' = 01000001
  = 65 ascii value of 'A'.
*/

#include <cstdio>
#include <cstring>
#include <cassert>
#include <ctime>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits>

using namespace std;

typedef unsigned long long UL;
typedef long long LL;
typedef pair<int,int> PII;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<LL> VL;
typedef vector<VL> VVL;
typedef vector<PII> VPII;
typedef vector<VPII> VVPII;

#define REP(i, n) for(int i = 0; i < (n); ++i)
#define FOR(i, st, nd) for(int i = (st); i < (nd); ++i)
#define SET(a, val) memset(a, val, sizeof(a))
#define mp make_pair

#define INF numeric_limits<int>::max()

void setBit(char &num, int bit) 
{
	num = num|(1<<(bit-1));
}

void solveDecodeTheTape()
{
	char line[20];
	char ascii;
	while(true) {
		fgets(line, 20, stdin);
		if(feof(stdin)) break;
		ascii = 0;
		int curBit = 8;
		for(int index = 0; line[index]; ++index) {
			if(line[index] == ' ') --curBit;
			else if(line[index] == 'o') setBit(ascii, curBit--);
		}
		if(ascii) printf("%c", ascii);
		//printf("%s", line);

		//printf("\n");
	}
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	// solve something here
	solveDecodeTheTape();

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}

