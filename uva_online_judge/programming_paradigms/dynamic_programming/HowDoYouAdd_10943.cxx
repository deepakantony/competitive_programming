// Problem A: How do you add?
// 
// Larry is very bad at math - he usually uses a calculator, which worked well 
// throughout college. Unforunately, he is now struck in a deserted island with 
// his good buddy Ryan after a snowboarding accident. They're now trying to 
// spend some time figuring out some good problems, and Ryan will eat Larry if 
// he cannot answer, so his fate is up to you!
// 
// It's a very simple problem - given a number N, how many ways can K numbers 
// less than N add up to N?
// 
// For example, for N = 20 and K = 2, there are 21 ways:
// 0+20
// 1+19
// 2+18
// 3+17
// 4+16
// 5+15
// ...
// 18+2
// 19+1
// 20+0
// 
// 
// Input
// 
// Each line will contain a pair of numbers N and K. N and K will both be an 
// integer from 1 to 100, inclusive. The input will terminate on 2 0's.
// Output
// 
// Since Larry is only interested in the last few digits of the answer, for 
// each pair of numbers N and K, print a single number mod 1,000,000 on a 
// single line. 
// 
// Sample Input
// 
// 20 2
// 20 2
// 0 0
// Sample Output
// 
// 21
// 21

#include <cstdio>
#include <cstring>

#define REP(i, st, n) for(int (i) = (st); (i) < (n); ++(i))

int memo[101][101];

int buildmemo()
{
	REP(n, 0, 101)
		memo[n][1] = 1;

	REP(n, 0, 101) 
		REP(k, 2, 101)
	{
		memo[n][k] = 0;
		REP(j, 0, n+1)
			memo[n][k] = (memo[n][k] + memo[j][k-1])%1000000;
	}
}

int main(int argc, char *argv[])
{
	buildmemo();
	int N,K;
	scanf(" %d %d", &N,&K);
	while(N!=0) 
	{
		printf("%d\n", memo[N][K]);
		scanf(" %d %d", &N,&K);
	}
}
		
