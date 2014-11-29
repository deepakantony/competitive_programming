#include <cstdio>
#include <cstring>

#define MAX 10000000
#define REP(i, st, n) for(int (i) = (st); (i) < (n); ++(i))

int primes[MAX];

int sumOfDigits(int n) {
	int sum = 0;
	while(n) {
		sum += n%10;
		n /= 10;
	}
	return sum;
}

int additivePrime(int n) { // use seive to find the nth additive prime
	if(n == 1) return 2; // i will not check for any even numbers
	memset(primes, 0, sizeof primes);
	primes[0] = 1;
	int curAdditiveIndex = 1;
	int curAdditivePrime = 2;
	REP(curPrime, 1, MAX) {
		if(primes[curPrime] == 0) { // it is prime
			int prime = 2*curPrime + 1;
			for(int mul = 3; ((prime*mul-1)/2) < MAX; mul+=2)
				primes[(prime*mul-1)/2] = 1;
			int sum = sumOfDigits(prime);
			if(sum == 2 || ((sum%2 != 0) && primes[(sum-1)/2] == 0)) {
				curAdditivePrime = prime;
				curAdditiveIndex++;
			}
			
		}
		if(curAdditiveIndex == n) break;
	}
	return curAdditiveIndex==n ? curAdditivePrime : 0;
	// return 0 if the additive prime was too far
}

int main(int argc, char *argv[])
{
	int n;
	scanf("%d", &n);
	printf("%d\n", additivePrime(n));
	return 0;
}
