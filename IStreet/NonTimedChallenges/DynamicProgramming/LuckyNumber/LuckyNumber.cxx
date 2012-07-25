#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_SUM_OF_SQUARES 1458 // (18 * 9 * 9) + 2
#define MAX_SUM_OF_DIGITS 162 // (18 * 9) + 2
#define TOTAL_DIGITS 18
#define LARGEST_NUM 1000000000000000000ll // 10^18

typedef long long vlong;

int primes[MAX_SUM_OF_SQUARES+1];



void initPrimes()
{
	primes[0] = primes[1] = 0;
	for(int index = 2; index <= MAX_SUM_OF_SQUARES; index++)
		primes[index] = -1;

	for(int index = 2; index <= MAX_SUM_OF_SQUARES; )
	{
		primes[index] = 1;
		int index2 = 2*index;
		while(index2 <= MAX_SUM_OF_SQUARES)
		{
			primes[index2] = 0;
			index2 += index;
		}

		while(index <= MAX_SUM_OF_SQUARES && primes[index] != -1)
			index++;
	}
}


// The solution is based on the solution given at 
// http://stackoverflow.com/questions/9018614/algorithm-to-find-lucky-numbers

vlong memo[TOTAL_DIGITS+2][MAX_SUM_OF_DIGITS+2][MAX_SUM_OF_SQUARES+2];
int kstart[TOTAL_DIGITS+1][MAX_SUM_OF_DIGITS+1];
int kend[TOTAL_DIGITS+1][MAX_SUM_OF_DIGITS+1];

void preProcess() {
	memset(memo, 0, sizeof memo);
	memo[0][0][0] = 1;
	
	for(int i = 0; i < TOTAL_DIGITS; ++i) {
		int jlimit = 9*i;
		int klimit = 81*i;
		for(int j = 0; j <= jlimit; ++j)
			for(int k = 0;  k <= klimit; ++k) 
				for(int l = 0; l < 10; ++l)
					memo[i+1][j+l][k+l*l] += memo[i][j][k];
	}

	for(int i = 0; i <= TOTAL_DIGITS; ++i) 
		for(int j = 0; j <= MAX_SUM_OF_DIGITS+1; ++j) {
			for(int k = 0; k <= MAX_SUM_OF_SQUARES; ++k)
				if(memo[i][j][k] != 0) { kstart[i][j] = k; break; }
			for(int k = MAX_SUM_OF_SQUARES+2; k >= 0; --k)
				if(memo[i][j][k] != 0) { kend[i][j] = k; break; }
		}
}

vlong res[TOTAL_DIGITS+1][10][MAX_SUM_OF_DIGITS+2][MAX_SUM_OF_SQUARES+2];

vlong luckyNumbersCount(vlong num) {
	int nDigits = 0;
	int digits[TOTAL_DIGITS];
	while(num > 0) {
		digits[nDigits++] = num%10;
		num/=10;
	}
	int sum = 0, sumSq = 0; 
	vlong result = 0;
	for(int i = nDigits-1; i >= 0; --i) {
		vlong stepRes = 0;
		int jlimit = 9*i;

		for(int l = 0; l < digits[i]; ++l)
			if(res[i][l][sum][sumSq] != -1) 
				stepRes += res[i][l][sum][sumSq];
			else {
				vlong step = 0;
				int lsum = l+sum;
				int llsum = l*l+sumSq;
				for(int j = 0; j <= jlimit; ++j) 
					if(primes[j+lsum])
						for(int k = kstart[i][j]; k <= kend[i][j]; ++k)
							if(primes[k+llsum]) {
								step += memo[i][j][k];
								stepRes += memo[i][j][k];
							}
				res[i][l][sum][sumSq] = step;
			}
		result += stepRes;
		sum += digits[i];
		sumSq += digits[i]*digits[i];
	}
	if(primes[sum] && primes[sumSq]) ++result;
	return result;
}

vlong luckyNumbersCountRange(vlong start, vlong end) {
	if(end == LARGEST_NUM) end--;
	return luckyNumbersCount(end) - luckyNumbersCount(start-1);
}

int main(int argc, char *argv[]) {
	clock_t start = clock();
	int T; scanf(" %d", &T);
	vlong A, B;
	initPrimes();
	preProcess();
	memset(res, -1, sizeof res);
	while(T--) {
		scanf(" %lld %lld", &A, &B);
		printf("%lld\n", luckyNumbersCountRange(A,B));
	}
	fprintf(stderr, "Time taken: %.3fs\n", (clock()-start)/(float)CLOCKS_PER_SEC);

	return 0;
}
