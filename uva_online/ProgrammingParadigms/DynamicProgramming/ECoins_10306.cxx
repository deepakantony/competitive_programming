// Problem G
// e-Coins
// Input: standard input
// Output: standard output
// Time Limit: 10 seconds
// Memory Limit: 32 MB
// At the Department for Bills and Coins, an extension of today's monetary 
// system has newly been proposed, in order to make it fit the new economy 
// better. A number of new so called e-coins will be produced, which, in 
// addition to having a value in the normal sense of today, also have an 
// InfoTechnological value. The goal of this reform is, of course, to make 
// justice to the economy of numerous dotcom companies which, despite the 
// fact that they are low on money surely have a lot of IT inside. All money 
// of the old kind will keep its conventional value and get zero 
// InfoTechnological value.
// 
// To successfully make value comparisons in the new system, something called 
// the e-modulus is introduced. This is calculated as SQRT(X*X+Y*Y), where X 
// and Y hold the sums of the conventional and InfoTechnological values 
// respectively. For instance, money with a conventional value of $3 
// altogether and an InfoTechnological value of $4 will get an e-modulus of 
// $5. Bear in mind that you have to calculate the sums of the conventional 
// and InfoTechnological values separately before you calculate the e-modulus 
// of the money.
// 
// To simplify the move to e-currency, you are assigned to write a program that, 
// given the e-modulus that shall be reached and a list of the different types 
// of e-coins that are available, calculates the smallest amount of e-coins that 
// are needed to exactly match the e-modulus. There is no limit on how many 
// e-coins of each type that may be used to match the given e-modulus.
// 
// Input
// A line with the number of problems n (0<n<=100), followed by n times:
// A line with the integers m (0<m<=40) and S (0<S<=300), where m indicates the 
// number of different e-coin types that exist in the problem, and S states the 
// value of the e-modulus that shall be matched exactly.
// m lines, each consisting of one pair of non-negative integers describing the 
// value of an e-coin. The first number in the pair states the conventional 
// value, and the second number holds the InfoTechnological value of the coin.
// When more than one number is present on a line, they will be separated by a 
// space. Between each problem, there will be one blank line.
//  
// Output
// The output consists of n lines. Each line contains either a single integer 
// holding the number of coins necessary to reach the specified e-modulus S or, 
// if S cannot be reached, the string "not possible".
// Sample Input:
// 3 
// 2 5 
// 0 2 
// 2 0
// 3 20 
// 0 2 
// 2 0 
// 2 1
// 3 5 
// 3 0 
// 0 4 
// 5 5
// Sample Output:
// not possible 
// 10 
// 2
// (Joint Effort Contest, Problem Source: Swedish National Programming Contest, 
// arranged by department of Computer Science at Lund Institute of Technology.)


#include <cstdio>
#include <cstring>

#define REP(i, st, n) for((i) = (st); (i) < (n); ++(i))

unsigned int memo[41][301][301];
int X[41], Y[41];

unsigned int min(unsigned int x,unsigned int y)
{
	return x>y?y:x;
}

void printMemo(int m, int s)
{
	int coin, xi, yi;
	REP(coin, 0, m+1)
	{
		printf("Coin: %d\n", coin);
		REP(xi, 0, s+1) {
			REP(yi, 0, s+1) {
				printf("%d ", memo[coin][xi][yi]);
			}
			printf("\n");
		}
	}
}

unsigned int minDP(int m, int s)
{
	unsigned int minCoins = -1;
	int coin, xi, yi;
	memset(memo, -1, sizeof memo);
	REP(coin, 1, m+1) memo[coin][0][0] = 0;

	REP(coin, 1, m+1) {
		REP(xi, 0, s+1) {
			REP(yi, 0, s+1) {
				if(xi == 0 && yi == 0) continue;

				if(X[coin] == 0) {
					if((yi-Y[coin]) >= 0 && memo[coin][xi][yi-Y[coin]] != -1) 
						memo[coin][xi][yi] = min(1+memo[coin][xi][yi-Y[coin]],
												 memo[coin-1][xi][yi]);
					else memo[coin][xi][yi] = memo[coin-1][xi][yi];
				}
				else if(Y[coin] == 0) {
					if((xi-X[coin]) >= 0 && memo[coin][xi-X[coin]][yi] != -1)
						memo[coin][xi][yi] = min(1+memo[coin][xi-X[coin]][yi],
												 memo[coin-1][xi][yi]);
					else memo[coin][xi][yi] = memo[coin-1][xi][yi];
				}
				else if((xi-X[coin]) >= 0 && (yi-Y[coin]) >= 0 &&
						memo[coin][xi-X[coin]][yi-Y[coin]] != -1)
						memo[coin][xi][yi] = min(1+memo[coin][xi-X[coin]][yi-Y[coin]],
												 memo[coin-1][xi][yi]);
				else memo[coin][xi][yi] = memo[coin-1][xi][yi];
				
				if((xi*xi + yi*yi) == s*s) {
					minCoins = min(minCoins, memo[coin][xi][yi]);
				}
			}
		}
	}
	return minCoins;
}

int main(int argc, char *argv[])
{
	int n, m, s, i;
	int res;
	scanf(" %d", &n);
	while(n--) {
		scanf(" %d %d", &m, &s);
		REP(i, 1, m+1) scanf(" %d %d", &X[i], &Y[i]);
		res = minDP(m,s);

		if(res < 0) printf("not possible\n");
		else printf("%d\n", res);
	}
	return 0;
}
