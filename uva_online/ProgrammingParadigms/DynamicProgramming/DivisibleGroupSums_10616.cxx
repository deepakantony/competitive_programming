
#include <cstdio>
#include <cstring>
#define REP(i, st, n) for(int (i) = (st); (i) < (n); ++(i))
#define RREP(i, st, n) for(int (i) = (st); (i) >= (n); --(i))
#define LL long long

int numbers[201];
LL memo[201][11][21];
int N, M;


LL mod(LL a, LL b) {
	LL res = a%b;
	return res<0 ? res+b : res;
}

LL buildMemo(int n, int m, int divisor, LL curSum)
{
	if(m>n) return 0;
	if(memo[n][m][curSu != -1) return memo[n][m];

	LL res = 0;
	if(m == 1) {
		RREP(i, n, 1) {
			if( mod(curSum+numbers[i], divisor) == 0)
				res++;
		}
	}
	else {
		RREP(i, n, 1) {
			res += buildMemo(i-1, m-1, divisor, curSum+numbers[i]);
		}
	}
//	return memo[n][m] = res;
	return res;
}

void printMemo(int divisor) {

		printf("DIVISOR - %d\n", divisor);
		REP(n, 1, N+1) {
			REP(m, 0, M+1) {
				printf("%lli ", memo[n][m]);
			}
			printf("\n");
		}

}

int main(int argc, char *argv[])
{
	int Q, D;
	int test = 1;
	for(scanf(" %d %d", &N, &Q); N != 0; 
		scanf(" %d %d", &N, &Q), test++)
	{
		REP(i, 1, N+1)
			scanf(" %d", &numbers[i]);
		
		printf("SET %d:\n", test);
		REP(i, 0, Q) {
			memset(memo, -1, sizeof memo);
			scanf(" %d %d", &D, &M);
			printf("QUERY %d: %llu\n", i+1, buildMemo(N, M, D, 0ll));
			printMemo(D);
		}

	}
}
