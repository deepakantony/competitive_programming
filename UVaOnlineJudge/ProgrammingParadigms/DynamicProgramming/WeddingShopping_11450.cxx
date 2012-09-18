// 
//  D. Wedding Shopping 
// 
// 
// Background
// 
// One of our best friends is getting married and we all are nervous because he 
// is the first of us who is doing something similar. In fact, we have never 
// assisted to a wedding, so we have no clothes or accessories, and to solve 
// the problem we are going to a famous department store of our city to buy 
// all we need: a shirt, a belt, some shoes, a tie, etcetera.
// 
// The Problem
// 
// We are offered different models for each class of garment (for example, 
// three shirts, two belts, four shoes, ..). We have to buy one model of each 
// class of garment, and just one.
// 
// As our budget is limited, we cannot spend more money than it, but we want 
// to spend the maximum possible. It's possible that we cannot buy one model 
// of each class of garment due to the short amount of money we have.
// 
// The Input
// 
// The first line of the input contains an integer, N, indicating the number 
// of test cases. For each test case, some lines appear, the first one 
// contains two integers, M and C, separated by blanks (1<=M<=200, and 
// 1<=C<=20), where M is the available amount of money and C is the number of 
// garments you have to buy. Following this line, there are C lines, each one 
// with some integers separated by blanks; in each of these lines the first 
// integer, K (1<=K<=20), indicates the number of different models for each 
// garment and it is followed by K integers indicating the price of each model 
// of that garment.
// 
// The Output
// 
// For each test case, the output should consist of one integer indicating 
// the maximum amount of money necessary to buy one element of each garment 
// without exceeding the initial amount of money. If there is no solution, 
// you must print "no solution".
// 
// Sample Input
// 
// 3
// 100 4
// 3 8 6 4
// 2 5 10
// 4 1 3 3 7
// 4 50 14 23 8
// 20 3
// 3 4 6 8
// 2 5 10
// 4 1 3 5 5
// 5 3
// 3 6 4 8
// 2 10 6
// 4 7 3 1 7
// Sample Output
// 
// 75
// 19
// no solution

#include <cstdio>
#include <algorithm>

#define REP(i, n) for(int (i) = 0; (i) < (n); ++i)

using namespace std;

int memo[210][25];
int model[25][25];
int M;

int maxSpent(int money, int garments)
{
	if(money < 0) return -2;
	if(garments == 0) return M - money;
	if(memo[money][garments] != -1) return memo[money][garments];
	int moneySpent = -2;
	REP(i, model[garments][0]) {
		moneySpent = max(moneySpent, maxSpent(money-model[garments][i+1], 
											  garments-1));
	}
	return memo[money][garments] = moneySpent;
}

int initMemo(int money, int garments)
{
	REP(i, money+1) REP(j, garments+1)
		memo[i][j] = -1;
}

int main(int argc, char *argv[])
{
	int nTests;
	scanf(" %d", &nTests);
	int C;
	while(nTests--) {
		scanf(" %d %d", &M, &C);
		REP(i, C) {
			scanf(" %d", &model[i+1][0]);
			REP(j, model[i+1][0]) {
				scanf(" %d", &model[i+1][j+1]);
			}
		}
		initMemo(M,C);
		int ans = maxSpent(M,C);
		if(ans <= 0)
			printf("no solution\n");
		else
			printf("%d\n", ans);
	}
}
