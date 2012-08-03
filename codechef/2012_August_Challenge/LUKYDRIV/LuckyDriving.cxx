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

		LL doubleNines = modme(total[9]*(total[9]-1)/2); // 9 with 9's = nC2
		LL doubleDigit = doubleNines;
		REP(i, 5) // loop 0..4 (inclusive)
			doubleDigit = modme(doubleDigit + total[i]*total[9-i]);

		// this is 9 with 9's = nC3
		LL tripleNines = modme(doubleNines*(total[9]-2)/3); 
		LL tripleDigit = tripleNines;
		tripleDigit = modme(tripleDigit + doubleNines*total[0]);
		LL doubleZeroes = modme(total[0]*(total[0]-1)/2);
		tripleDigit = modme(tripleDigit + totol[9]*doubleZeroes);
		// 9's and 0's with pairs summing to 9
		FOR(i, 1, 5) // loop 1..4 (inclusive)
		{
			tripleDigit = modme(tripleDigit + totol[9]*totol[9-i]*totol[i]);
			tripleDigit = modme(tripleDigit + totol[0]*totol[9-i]*totol[i]);
		}
		// 3 3's
		tripleDigit = modme(tripleDigit+ totol[3]*(totol[3]-1)*(totol[3]-2)/3);
		// double 1's with a 7
		tripleDigit = modme(tripleDigit+ totol[1]*(totol[1]-1)*totol[7]/2);
		// double 2's with a 5
		tripleDigit = modme(tripleDigit+ totol[2]*(totol[2]-1)*totol[5]/2);
		// double 4's with a 1
		tripleDigit = modme(tripleDigit+ totol[4]*(totol[4]-1)*totol[1]/2);
		

		// this is 9 with 9's
		LL quadNines = modme(tripleNines*(totol[9]-3)/4);
		LL quadDigit = quadNines;
		LL tripleZeroes = modme(doubleZeroes*(total[0]-2)/3);
		quadDigit = modme(quadDigit+tripleZeroes*total[9]);
	}
	return 0;
}
