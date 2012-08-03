#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define MOD 1000000007
typedef long long LL;

LL modme(LL num) {
	return num < 0 ? num + MOD : num%MOD;
}

#define REP(i, n) for(int i = 0; i < (n); ++i)
#define FOR(i, st, nd) for(int i = (st); i < (nd); ++i)

int main(int argc, char *argv[])
{
	int T; scanf("%d", &T);
	char digSeq[10010];
	int total[10];
	while(T--) {
		scanf("%s", digSeq);
		int numOfDigs = strlen(digSeq);
		memset(total, 0, sizeof total);
		REP(i, numOfDigs) ++total[int(digSeq[i]-'0')];

		LL singleDigit = total[9]; // just 9's can total to 9 when single digit

		// 9 with 9's = nC2
		LL doubleNines = total[9] > 1 ? modme(total[9]*(total[9]-1)/2) : 0; 
		LL doubleDigit = doubleNines;
		LL doubleNo9sAnd0s = 0;
		FOR(i, 1, 5) // loop 1..4 (inclusive)
			doubleNo9sAnd0s = modme(doubleNo9sAnd0s + total[i]*total[9-i]);
		doubleDigit = modme(doubleDigit + doubleNo9sAnd0s + total[9]*total[0]);

		// this is 9 with 9's = nC3
		LL tripleNines = total[9] > 1 ? modme(doubleNines*(total[9]-2)/3) : 0; 
		LL tripleDigit = tripleNines;
		tripleDigit = modme(tripleDigit + doubleNines*total[0]);
		LL doubleZeroes = total[0] > 1 ? modme(total[0]*(total[0]-1)/2) : 0;
		tripleDigit = modme(tripleDigit + total[9]*doubleZeroes);
		// 9's and 0's with pairs summing to 9
		tripleDigit = modme(tripleDigit + total[9]*doubleNo9sAnd0s);
		tripleDigit = modme(tripleDigit + total[0]*doubleNo9sAnd0s);
		// 3 3's
		LL tripleNo0sND9s = 0;
		if(total[3] > 2)
			tripleNo0sND9s = modme(tripleNo0sND9s+ total[3]*(total[3]-1)*(total[3]-2)/6);
		// 3 6's
		
		// double 1's with a 7
		if(total[1] > 1)
			tripleNo0sND9s = modme(tripleNo0sND9s+ total[1]*(total[1]-1)*total[7]/2);
		// double 2's with a 5
		if(total[2] > 1)
			tripleNo0sND9s = modme(tripleNo0sND9s+ total[2]*(total[2]-1)*total[5]/2);
		// double 4's with a 1
		if(total[4] > 1)
			tripleNo0sND9s = modme(tripleNo0sND9s+ total[4]*(total[4]-1)*total[1]/2);
		tripleDigit = modme(tripleDigit+tripleNo0sND9s);

		// this is 9 with 9's
		LL quadNines = total[9] > 3 ? modme(tripleNines*(total[9]-3)/4) : 0;
		LL quadDigit = quadNines;
		// 9's with 0's
		LL tripleZeroes = total[0] > 2 ? modme(doubleZeroes*(total[0]-2)/3) : 0;
		quadDigit = modme(quadDigit+tripleZeroes*total[9]);
		quadDigit = modme(quadDigit+doubleZeroes*doubleNines);
		quadDigit = modme(quadDigit+total[0]*tripleNines);
		// 9's with triple no nines and zeroes
		quadDigit = modme(quadDigit+total[9]*tripleNo0sND9s);
		// 0's with triple no nines and zeroes
		quadDigit = modme(quadDigit+total[0]*tripleNo0sND9s);
		// 2 9's with pairs having no 0's or 9's
		quadDigit = modme(quadDigit+doubleNines*doubleNo9sAnd0s);
		// 2 0's with pairs having no 0's or 9's
		quadDigit = modme(quadDigit+doubleZeroes*doubleNo9sAnd0s);
		// 9's and 0's pairs having no 0's and 9's
		quadDigit = modme(quadDigit+total[0]*total[9]*doubleNo9sAnd0s);
		// triple 1's with 6's
		LL triple1s = total[1] > 2? modme(total[1]*(total[1]-1)*(total[1]-2)/6) : 0;
		quadDigit = modme(quadDigit + triple1s*total[6]);
		// triple 2's with 1's
		LL triple2s = total[2] > 2? modme(total[2]*(total[2]-1)*(total[2]-2)/6) : 0;
		quadDigit = modme(quadDigit + triple2s*total[1]);
		
		
	}
	return 0;
}
