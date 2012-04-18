//   Coin Change 
// Suppose there are 5 types of coins: 50-cent, 25-cent, 10-cent, 5-cent, and 
// 1-cent. We want to make changes with these coins for a given amount of 
// money.
// 
// 
// For example, if we have 11 cents, then we can make changes with one 10-cent 
// coin and one 1-cent coin, two 5-cent coins and one 1-cent coin, one 5-cent 
// coin and six 1-cent coins, or eleven 1-cent coins. So there are four ways of
//  making changes for 11 cents with the above coins. Note that we count that 
// there is one way of making change for zero cent.
// 
// 
// Write a program to find the total number of different ways of making changes 
// for any amount of money in cents. Your program should be able to handle up 
// to 7489 cents.
// 
// Input 
// 
// The input file contains any number of lines, each one consisting of a number 
// for the amount of money in cents.
// Output 
// 
// For each input line, output a line containing the number of different ways 
// of making changes with the above 5 types of coins.
// Sample Input 
// 
// 11
// 26
// Sample Output 
// 
// 4
// 13
// 
// 
// Miguel Revilla 
// 2000-08-14
// 

#include <cstdio>
#include <cstring>

typedef unsigned long long ULL;

int coins[] = {1, 5, 10, 25, 50};
int memo[5][7490];

int numWaysCC(int curCoinIdx, int money)
{
	if(money == 0) return 1;
	if(memo[curCoinIdx][money] != -1) return memo[curCoinIdx][money];
	if(curCoinIdx == 0) return memo[curCoinIdx][money] = 1;
	if(money < coins[curCoinIdx]) 
		return memo[curCoinIdx][money] = numWaysCC(curCoinIdx-1, money);
	else return memo[curCoinIdx][money] = 
			 numWaysCC(curCoinIdx-1, money) + 
			 numWaysCC(curCoinIdx, money-coins[curCoinIdx]);
}

int main(int argc, char *argv[])
{
	int money;
	memset(memo, -1, sizeof memo);
	while(scanf(" %d", &money) != EOF) {
		printf("%d\n", numWaysCC(4, money));
	}
	return 0;
}
