#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <bitset>
#include <valarray>
#include <iterator>

using namespace std;

#define PRIME_N 10000000

#define REP(i, st, n) for(int (i) = st; (i) < (n); ++(i))
#define ULL unsigned long long
#define VULL vector<ULL>
#define VI vector<int>
#define ValI valarray<int>
#define P_ULL pair<ULL, ULL>

VULL allPrimes;

template<class T>
void print(T container)
{
	for(typename T::iterator it = container.begin();
		it != container.end(); ++it)
		cout << *it << " ";
	cout << endl;
}

ULL gcd(ULL a, ULL b) {
	return b ? gcd(b, a%b) : a;
}

int numOfDivisors(VI &primePower)
{
	int prod = 1;
	REP(i, 0, primePower.size())
		prod *= primePower[i]+1;

	return prod;
}

void findPrimeFactors(ULL n, VI &primeFactors, VI &primePower)
{
	int sqrtN = ceil(sqrt(n));
	REP(i, 0, allPrimes.size()) {
		if(allPrimes[i] > n || allPrimes[i] > sqrtN) break;
		if(n%allPrimes[i] == 0) {
			primeFactors.push_back(allPrimes[i]);
			int factorPower = 1;
			n/=allPrimes[i];
			while(n > 1 && n%allPrimes[i] == 0) {
				factorPower++;
				n/=allPrimes[i];
			}
			primePower.push_back(factorPower);
		}
	}
	if(n > 1) { primeFactors.push_back(n); primePower.push_back(1); }

}

void generatePrimes()
{ // seive
	bitset<PRIME_N> *bset = new bitset<PRIME_N>();
	bset->set();
	allPrimes.push_back(2);
	allPrimes.push_back(3);
	for(int i = 5; i < PRIME_N; i = i + 4)
	{
		if((*bset)[i]) {
			allPrimes.push_back(i);
			for(int j = i*2; j < PRIME_N; j+=i)
				bset->reset(j);
		}
		i = i+2;
		if(i < PRIME_N && (*bset)[i]) {
			allPrimes.push_back(i);
			for(int j = i*2; j < PRIME_N; j+=i)
				bset->reset(j);
		}
	}
}

ULL multiply(VI &arr)
{
	ULL prod = 1;
	REP(i, 0, arr.size())
		prod *= arr[i];
	return prod;
}

ULL powProd(VI &primeFactors, VI &primePowers) 
{
	ULL prod = 1;
	REP(i, 0, primeFactors.size())
		prod *= (ULL)pow((double)primeFactors[i], primePowers[i]);

	return prod;
}

void constructDivisorSet(set<ULL> &divSet, VI &primeFactors, 
						 VI &primePower) 
{
	VI primeIndex(primePower.size(), 0);
	divSet.clear();
	while(primeIndex.size() > 0) {
		divSet.insert(powProd(primeFactors, primeIndex));
		primeIndex[primeIndex.size()-1]++;
		for(int i = primeIndex.size()-1; i>=0 && 
				primeIndex[i] > primePower[i]; i--)
		{
			primeIndex[i] = 0;
			if((i-1) < 0) return;
			primeIndex[i-1]++;
		}
	}
	if(divSet.size() == 0) divSet.insert(1);
}

P_ULL getMaxNumOfDivisorsPrimeMethodApprx(ULL limit) {
	generatePrimes();
	ULL prod = 1;
	int prime = 0;
	while(prod <= limit) {
		if(prod * 2 > limit) break;

		if(prod*allPrimes[prime] > limit) 
			prime = 0;
		else 
			prod *= allPrimes[prime++];
	}
	VI primeFactors, primePower;
	findPrimeFactors(prod, primeFactors, primePower);
	int ndivs = numOfDivisors(primePower);

	printf("%d\n", (int) primePower.size());

	return make_pair(prod, ndivs);
}

P_ULL getMaxNumOfDivisors(ULL limit) {
	generatePrimes();
	int maxDivs = 1;
	ULL number = 1;
	for(int i = limit; i > maxDivs; i--) {
		VI primeFactors, primePower;
		findPrimeFactors(i, primeFactors, primePower);
		ULL ndivs = numOfDivisors(primePower);
		if(ndivs > maxDivs) {
			number = i;
			maxDivs = ndivs;
		}
	}
	return make_pair(number, maxDivs);
}

void getmax() {
	P_ULL p = getMaxNumOfDivisorsPrimeMethodApprx(10000000000000llu);
	printf("Highest number of divisors: (%llu, %llu)\n", 
		   p.first, p.second);
}



void solveUnfriendlyNumbersFast(int N, ULL K, ULL *unfriendly) 
{
	generatePrimes();
	VI primeFactors, primePower;
	findPrimeFactors(K, primeFactors, primePower);
	set<ULL> divSet;
	constructDivisorSet(divSet, primeFactors, primePower);
	REP(i, 0, N) {
		ULL g = gcd(K, unfriendly[i]);
	
		set<ULL>::iterator it = divSet.begin();
		while(it != divSet.end() && g >= *it) {
			if(g% (*it) == 0) {
				ULL temp = *it;
				divSet.erase(it);
				it = divSet.upper_bound(temp);
			}
			else ++it;
		}
		if(divSet.size() == 0) break;
	}
	printf("%d\n", (int)divSet.size());
}

void getSlowDivisors(int K, VI &divisors) {
	divisors.clear();
	divisors.push_back(K);
	REP(i, 1, (K/2)+1) 
		if(K%i == 0)
			divisors.push_back(i);	
	sort(divisors.begin(), divisors.end());
}

void getFastDivisors(int K, set<int> &divSet) 
{
	divSet.clear();
	VI pf, pp;
	findPrimeFactors(K, pf, pp);
	set<ULL> divs;
	constructDivisorSet(divs, pf, pp);
	for(set<ULL>::iterator it = divs.begin(); it!= divs.end(); ++it)
		divSet.insert((int)*it);
}

void buildUnfriendly(int *unfriendly, int limit)
{
	REP(i, 0, limit)
		unfriendly[i] = rand() % limit;
}

void removeDivsSlow(int K, VI &divisors, int *unfriendly, int limit)
{
	REP(i, 0, limit) {
		REP(j, 0, divisors.size()) {
			if(divisors[j] && unfriendly[i] % divisors[j]  == 0)
				divisors[j] = 0;
		}
	}
	int uf = 0;
	VI temp(divisors.begin(), divisors.end());
	divisors.clear();
	REP(i, 0, temp.size())
		if(temp[i])
			divisors.push_back(temp[i]);
	//sort(divisors.begin(), divisors.end());
}

void removeDivsFast(int K, set<int> &divSet, int *unfriendly, int limit)
{
	REP(i, 0, limit) {
		int g = gcd(K, unfriendly[i]);
	
		set<int>::iterator it = divSet.begin();
		while(it != divSet.end() && g >= *it) {
			if(g% (*it) == 0) {
				int temp = *it;
				divSet.erase(it);
				it = divSet.upper_bound(temp);
			}
			else ++it;
		}
		if(divSet.size() == 0) break;
	}	
}

void verifyFastAlgo()
{
	generatePrimes();
	vector<int> divisors;
	set<int> divSet;
	int unfriendly[1000010];
	int limit = 1000;
	buildUnfriendly(unfriendly, limit);
	for(int K = 1; K < 3000001; K++) {
		printf("%d\r", K);
		getSlowDivisors(K, divisors);
		getFastDivisors(K, divSet);
		removeDivsSlow(K, divisors, unfriendly, limit);
		removeDivsFast(K, divSet, unfriendly, limit);

		if(mismatch(divisors.begin(), divisors.end(), divSet.begin()).first
		   != divisors.end()) 
		{

			printf("\nMismatch: %d\n",K);
			cout << "Slow version: " << endl;
			print(divisors);
			cout << endl << "Fast version: " << endl;
			print(divSet);
			cout << endl;
			return;

		}

	}

}

void solveProb() {
	int N;
	ULL K;
	ULL unfriendly[1000010];
	scanf(" %d %llu", &N, &K);
	REP(i, 0, N) scanf(" %llu", &unfriendly[i]);
	solveUnfriendlyNumbersFast(N, K, unfriendly);
}

int main(int argc, char *argv[])
{
	clock_t start = clock();


	//solveProb();
	verifyFastAlgo();

	fprintf(stderr, "Time Taken: %.3f\n", 
			((double)(clock()-start))/CLOCKS_PER_SEC);
	return 0;
}


