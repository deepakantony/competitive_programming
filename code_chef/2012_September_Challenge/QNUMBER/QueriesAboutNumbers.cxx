/*
  Problem: Queries About Numbers
  Link: http://www.codechef.com/SEP12/problems/QNUMBER
  Author: deebee - Deepak Antony
  Solution: Find the prime factors of N. Use these prime factors for finding 
  the remaining answers.
*/

#include <cstdio>
#include <cstring>
#include <cassert>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long LL;
typedef unsigned long long UL;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<LL> VL;
typedef vector<VL> VVL;

#define REP(i, n) for(int i = 0; i < (n); ++i)
#define FOR(i, st, nd) for(int i = (st); i < (nd); ++i)
#define SET(a, val) memset(a, val, sizeof(a))

namespace mathutil {
	template<class T> 
	T gcd(T a, T b) { 
		if(a<b) return gcd(b, a);
		if(b==0) return a;
		return gcd(b, a%b);
	}
}

LL primeFactors[11];
LL pfPowers[11];
int totalPf; 

void findPrimeFactors(LL N) {
	SET(pfPowers, 0);
	totalPf = 0;

	if(N%2 == 0) {
		primeFactors[totalPf] = 2;
		while(N%2 == 0) {
			pfPowers[0]++;
			N >>= 1;
		}
		totalPf++;
	}
	if(N%3 == 0) {
		primeFactors[totalPf] = 3;
		while(N%3 == 0) {
			pfPowers[totalPf]++;
			N /= 3;
		}
		++totalPf;
	}

	int seive[1000000]; SET(seive, 0);
	int curPrime = 5, step = 2;
	
	while(N>1 && curPrime < 1000000) {
		if(seive[curPrime]==0) {
			for(int i = curPrime*2; i < 1000000; i+= curPrime)
				seive[i] = 1;

			if(N%curPrime == 0) {
				primeFactors[totalPf] = curPrime;
				while(N%curPrime == 0) {
					pfPowers[totalPf]++;
					N /= curPrime;
				}
				++totalPf;
			}
		}

		curPrime += step;
		step = (step==2) ? 4 : 2;
	}

	if(N>1) {
		primeFactors[totalPf] = N, pfPowers[totalPf]++;
		++totalPf;
	}
}

LL relPrimeFactors[11];
LL relPfPowers[11];
int relTotalPF;
void relativePrimeFactors(LL N) {
	SET(relPfPowers, 0);
	relTotalPF = 0;
	
	REP(i, totalPf) {
		if(N <= 1) break;
		if(N%primeFactors[i] == 0) {
			relPrimeFactors[relTotalPF] = primeFactors[i];
			while(N%primeFactors[i] == 0) {
				relPfPowers[relTotalPF]++;
				N /= primeFactors[i];
			}
			relTotalPF++;
		}
	}
}

LL numberOfDivisors(LL *pfPows, int pf) {
	LL prod = 1;
	REP(i, pf) prod *= (pfPows[i]+1);
	return prod;
}

void unitTests() {
	findPrimeFactors(9*8);
	printf("%d : ", 9*8);
	REP(i, totalPf) printf("(%lld^%lld)", primeFactors[i], pfPowers[i]);
	printf(" : %lld\n", numberOfDivisors(pfPowers, totalPf));

	findPrimeFactors(9*8*49);
	printf("%d : ", 9*8*49);
	REP(i, totalPf) printf("(%lld^%lld)", primeFactors[i], pfPowers[i]);
	printf(" : %lld\n", numberOfDivisors(pfPowers, totalPf));

	findPrimeFactors(49*882377ll*882377ll);
	printf("%lld : ", 49*882377ll*882377);
	REP(i, totalPf) printf("(%lld^%lld)", primeFactors[i], pfPowers[i]);
	printf(" : %lld\n", numberOfDivisors(pfPowers, totalPf));

	findPrimeFactors(2ll*3*5*7*9*11*13*17*19*23*29*31*33);
	printf("%lld : ", 2ll*3*5*7*9*11*13*17*19*23*29*31*33);
	REP(i, totalPf) printf("(%lld^%lld)", primeFactors[i], pfPowers[i]);
	printf(" : %lld\n", numberOfDivisors(pfPowers, totalPf));

	
}

void solveQNUMBER() {
	LL N, K; int Q, T;
	scanf("%lld %d", &N, &Q);
	
	// Find the prime factors of N
	findPrimeFactors(N);
	LL divisorsOfN = numberOfDivisors(pfPowers, totalPf);
	while(Q--) {
		scanf("%d %lld", &T, &K);
		// using the prime factors of N, find the ans
		switch(T) {
		case 1:
			// find the total divisors of gcd(N, K)
			relativePrimeFactors(mathutil::gcd(N,K));
			printf("%lld\n", numberOfDivisors(relPfPowers, relTotalPF));
			break;
		case 2:
			// find the total divisors of N/K if N%K==0 or else 0
			if(N%K == 0) {
				relativePrimeFactors(N/K);
				printf("%lld\n", numberOfDivisors(relPfPowers, relTotalPF));				
			}
			else printf("0\n");
			break;
		case 3:
			// Total divisors for N - (subtraction)
			// find the total divisors of N/K if N%K==0 or else 0
			if(N%K != 0) 
				printf("%lld\n", divisorsOfN);
			else {
				relativePrimeFactors(N/K);
				printf("%lld\n", 
					   divisorsOfN - numberOfDivisors(relPfPowers, relTotalPF));
			}
			
			break;
		}
	}
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	// solve something here
	solveQNUMBER();
#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
