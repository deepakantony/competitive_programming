// 
//  Dollars 
// 
// New Zealand currency consists of $100, $50, $20, $10, and $5 notes and 
// $2, $1, 50c, 20c, 10c and 5c coins. Write a program that will determine, 
// for any given amount, in how many ways that amount may be made up. 
// Changing the order of listing does not increase the count. Thus 20c may 
// be made up in 4 ways: 1  20c, 2  10c, 10c+2  5c, and 4  5c.
// 
// Input
// 
// Input will consist of a series of real numbers no greater than $300.00 
// each on a separate line. Each amount will be valid, that is will be a 
// multiple of 5c. The file will be terminated by a line containing zero 
// (0.00).
// 
// Output
// 
// Output will consist of a line for each of the amounts in the input, each 
// line consisting of the amount of money (with two decimal places and 
// right justified in a field of width 6), followed by the number of ways 
// in which that amount may be made up, right justified in a field of width 
// 17.
// 
// Sample input
// 
// 0.20
// 2.00
// 0.00
// Sample output
// 
//   0.20                4
//   2.00              293
// 

#include <cstdio>
#include <cstring>
#include <ctime>

using namespace std;

int dollars[] = {5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000};
unsigned long long memo[11][30010];

unsigned long long numWays(int n, int money) {
	if(money == 0) return 1;
	if(money < 0 || n < 0) return 0;
	if(memo[n][money] != -1) return memo[n][money];

	return memo[n][money] = numWays(n, money - dollars[n]) + 
		numWays(n-1, money);
}

int main(int argc, char *argv[])
{
	clock_t start = clock();
	int money;
	int dec, frac;
	memset(memo, -1, sizeof memo);
	while(scanf(" %d.%d", &dec, &frac), money=dec*100+frac, money != 0)
		printf("%6.2f%17llu\n", money/100.00, numWays(10, money));

	fprintf(stderr, "Time taken: %.3f\n", 
			((double)(clock()-start))/CLOCKS_PER_SEC);
	return 0;
}
