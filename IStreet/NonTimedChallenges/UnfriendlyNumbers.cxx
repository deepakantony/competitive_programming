// There is one friendly number and N unfriendly numbers. We want to find 
// how many numbers are there which exactly divide the friendly number, but 
// does not divide any of the unfriendly numbers.
// 
// Input Format:
// The first line of input contains two numbers N and K seperated by spaces. 
// N is the number of unfriendly numbers, K is the friendly number.
// The second line of input contains N space separated unfriendly numbers.
//  
// Output Format:
// Output the answer in a single line.
//  
// Constraints:
// 1 <= N <= 10^5
// 1 <= K <= 10^6
// 1 <= unfriendly numbers <= 10^18
//  
// Sample Input:
// 8 16
// 2 5 7 4 3 8 3 18
//  
// Sample Output:
// 1
//  
// Explanation :
// Divisors of the given friendly number 16, are { 1, 2, 4, 8, 16 } and the 
// unfriendly numbers are {2, 5, 7, 4, 3, 8, 3, 18}. Now 1 divides all 
// unfriendly numbers, 2 divide 2, 4 divide 4, 8 divide 8 but 16 divides 
// none of them. So only one number exists which divide the friendly number 
// but does not divide any of the unfriendly numbers. So the answer is 1.   
// 

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <ctime>
#include <cmath>
#include <cstring>

using namespace std;

#define REP(i, st, n) for(int (i) = (st); (i) < (n); ++(i))

typedef unsigned long long ull;

#define F_SIZE 1010
#define P_SIZE 100
#define N_SIZE 100010

int N, K, nPF;
int primes[F_SIZE];
int prime_factors[P_SIZE];
int factor_power[P_SIZE];
int uf_factors[P_SIZE];
ull uf_numbers[N_SIZE];

void init_prime_factors() 
{
	int num = K;
	int sqrtNum = (int)ceil(sqrt(num)) + 1;
	memset(primes, 1, (sqrtNum+1)*sizeof(int));
	nPF = 0;
	primes[0] = primes[1] = 0;
	for(int prime = 2; prime < sqrtNum && num > 1; ++prime) {
		if(primes[prime]) {
			for(int mul = 2; mul*prime <= sqrtNum; mul++) 
				primes[mul*prime] = 0;
			if(num%prime == 0) { 
				prime_factors[nPF] = prime; 
				uf_factors[nPF] = 0;
				factor_power[nPF++] = 1; 
				num /= prime;
			}
			while(num > 1 && (num%prime == 0)) {
				num /= prime; factor_power[nPF-1]++;
			}
		}
	}
	if(num > 1) {
		prime_factors[nPF] = num;
		factor_power[nPF++] = 1;
	}
}

int number_of_divisors()
{
	int div = 1;
	REP(i, 0, nPF)
		div *= factor_power[i]+1;
	return div;
}

void printMax(int limit) {
	int m = 1;
	REP(i, 1, limit) {
		K = i;
		init_prime_factors();
		m = max(m, number_of_divisors());
	}
	printf("%d\n", m);
}


void printFactors() 
{
	REP(i, 0, nPF) {
		printf("%d^%d,", prime_factors[i], factor_power[i]);
	}
	printf("\n");
}

void subtract_factors() 
{
	REP(i, 0, nPF) {
		int curPrime = prime_factors[i];
		for(int uf = 0; factor_power[i] != uf_factors[i] && uf < N; uf++) {
			while(factor_power[i] != uf_factors[i] && 
				  uf_numbers[uf]%curPrime == 0) {
				curPrime *= prime_factors[i];
				uf_factors[i]++;
			}
		}
	}
}

void printSubFactors()
{
	REP(i, 0, nPF) {
		printf("%d^%d,", prime_factors[i], uf_factors[i]);
	}
	printf("\n");
	REP(uf, 0, N) 
		printf("%llu,", uf_numbers[uf]);
	printf("\n");
}

int solve() {
	if(K == 1) return 0;
	REP(i, 0, nPF) 
		if(uf_numbers[i] % K == 0) return 0;
		
	int prod = 1;
	int onlyOne = 1;
	REP(i, 0, nPF) {
		if(factor_power[i]-uf_factors[i]) 
			prod *= (factor_power[i] - uf_factors[i] + 1);
		if(uf_factors[i] != 0)
			onlyOne = 0;
	}
	//if(onlyOne) return prod-1;
	return prod == 1 ? 0 : prod-1;
}

int solveUnfriendlyNumbers()
{
	vector<int> divisors;
	divisors.push_back(K);
	REP(i, 2, (K/2)+1) 
		if(K%i == 0)
			divisors.push_back(i);

	REP(i, 0, N) {
		REP(j, 0, divisors.size()) {
			if(divisors[j] && uf_numbers[i] % divisors[j]  == 0)
				divisors[j] = 0;
		}
	}
	int uf = 0;
	REP(i, 0, divisors.size())
		if(divisors[i]) uf++;
	return uf;
}

int main(int argc, char *argv[])
{
	clock_t start = clock();
	scanf(" %d %d\n", &N, &K);
	REP(i, 0, N) 
		//scanf(" %llu", &uf_numbers[i]);
		cin >> uf_numbers[i];

//	init_prime_factors();
//	printFactors();
//	subtract_factors();
//	printSubFactors();
	printf("%d\n", solveUnfriendlyNumbers());

	clock_t end = clock();
	fprintf(stderr, "%.4fs\n", (double)(end-start)/CLOCKS_PER_SEC);
	return 0;
}
