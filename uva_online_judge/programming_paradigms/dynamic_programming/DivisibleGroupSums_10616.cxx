// Divisible Group Sums
// Input: Standard Input
// Output: Standard Output
// Time Limit: 1 Second
//  
// Given a list of N numbers you will be allowed to choose any M of them. So 
// you can choose in NCM ways. You will have to determine how many of these 
// chosen groups have a sum, which is divisible by D.
//  
// Input
// The input file contains maximum ten sets of inputs. The description of each 
// set is given below.
//  
// The first line of each set contains two integers N (0<N<=200) and Q 
// (0<Q<=10). Here N indicates how many numbers are there and Q is the total
//  no of query. Each of the next N lines contains one 32 bit signed integer. 
// Our queries will have to be answered based on these N numbers. Next Q lines 
// contain Q queries. Each query contains two integers D (0<D<=20) and
//  M (0<M<=10) whose meanings are explained in the first paragraph.
//  
// Input is terminated by a case whose N=0 and Q=0. This case should not be 
// processed.
//  
// Output
// For each set of input, print the set number. Then for each query in the set 
// print the query number followed by the number of desired groups. See sample 
// output to know the exact output format.
//  
// Sample Input                             Output for Sample Input
// 10 2
// 1
// 2
// 3
// 4
// 5
// 6
// 7
// 8
// 9
// 10
// 5 1
// 5 2
// 5 1
// 2
// 3
// 4
// 5
// 6
// 6 2
// 0 0
// SET 1:
// QUERY 1: 2
// QUERY 2: 9
// SET 2:
// QUERY 1: 1
// Problemsetter: Shahriar Manzoor, Member of Elite Problemsetters' Panel


#include <cstdio>
#include <cstring>
#define REP(i, st, n) for(int (i) = (st); (i) < (n); ++(i))
#define RREP(i, st, n) for(int (i) = (st); (i) >= (n); --(i))
#define LL long long

int numbers[201];
LL memo[201][11][21];
int N, M, D;


LL mod(LL a, LL b) {
	LL res = a%b;
	return res<0 ? res+b : res;
}

LL buildMemo(int n, int m, int curSum)
{
	if(m>n) return 0;
	if(memo[n][m][curSum] != -1) return memo[n][m][curSum];

	if(m==0) return memo[n][m][curSum] = curSum==0 ? 1 : 0;
	if(n==0) return 0;
	return memo[n][m][curSum] = 
		buildMemo(n-1, m-1, mod(curSum+numbers[n], D)) +
		buildMemo(n-1, m, curSum);
}

void printMemo() 
{
	REP(divisor, 0, D+1) {
	printf("DIVISOR - %d\n", divisor);
	REP(n, 1, N+1) {
		REP(m, 0, M+1) {
			printf("%lli ", memo[n][m][divisor]);
		}
		printf("\n");
	}
	}
}

int main(int argc, char *argv[])
{
	int Q;
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
			printf("QUERY %d: %lli\n", i+1, buildMemo(N, M, 0));
			//printMemo();
		}

	}
}
