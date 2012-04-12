// SuperSale
// 
// There is a SuperSale in a SuperHiperMarket. Every person can take only one 
// object of each kind, i.e. one TV, one carrot, but for extra low price. We are 
// going with a whole family to that SuperHiperMarket. Every person can take as
//  many objects, as he/she can carry out from the SuperSale. We have given list 
// of objects with prices and their weight. We also know, what is the maximum 
// weight that every person can stand. What is the maximal value of objects we 
// can buy at SuperSale?
// 
// Input Specification
// 
// The input consists of T test cases. The number of them (1<=T<=1000) is given 
// on the first line of the input file.
// Each test case begins with a line containing a single integer number N that 
// indicates the number of objects (1 <= N <= 1000). Then follows N lines, each
//  containing two integers: P and W. The first integer (1<=P<=100) corresponds 
// to the price of object. The second  integer (1<=W<=30) corresponds to the 
// weight of object. Next line contains one integer (1<=G<=100)  it’s the number 
// of people in our group. Next G lines contains maximal weight (1<=MW<=30) that 
// can stand this i-th person from our family (1<=i<=G).
// Output Specification
// 
// For every test case your program has to determine one integer. Print out the
//  maximal value of goods which we can buy with that family.
// Sample Input
// 
// 2
// 3
// 72 17
// 44 23
// 31 24
// 1
// 26
// 6
// 64 26
// 85 22
// 52 4
// 99 18
// 39 13
// 54 9
// 4
// 23
// 20
// 20
// 26
//  
// Output for the Sample Input
// 
// 72
// 514
//  

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define REP(i, st, n) for(int (i) = (st); (i) < (n); ++(i))

int memo[31][1000];
int N;
int price[1000], weight[1000];

void buildMemo() {
	REP(wt, 0, 31) {
		REP(item, 0, N) {
			memo[wt][item] = 0;
			if(item > 0)
				if(wt >= weight[item]) 
					memo[wt][item] = max(
						memo[wt-weight[item]][item-1] + price[item],
						memo[wt][item-1]);
				else memo[wt][item] = memo[wt][item-1];
			else if(wt >= weight[item])
				memo[wt][item] = price[item];
		}
	}
}

int main(int argc, char *argv[])
{

	int nTests; scanf(" %d", &nTests);
	int totalPrice, mw, G;
	while(nTests--) {
		scanf(" %d", &N);
		REP(i, 0, N) scanf(" %d %d", &price[i], &weight[i]);

		buildMemo();
		scanf(" %d", &G);
		totalPrice = 0;
		REP(i, 0, G) {
			scanf(" %d", &mw);
			totalPrice += memo[mw][N-1];
		}
		printf("%d\n", totalPrice);
	}
	return 0;
}
