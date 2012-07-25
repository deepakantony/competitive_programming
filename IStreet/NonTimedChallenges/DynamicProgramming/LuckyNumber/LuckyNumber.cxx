#include <string>
#include <algorithm>
#include <vector>
#include <numeric>
#include <list>
#include <iterator>

using namespace std;

#define MAX_SUM_OF_SQUARES 1459 // (18 * 9 * 9) + 1
#define MAX_SUM_OF_DIGITS 163 // (18 * 9) + 1

typedef unsigned long long vlong;

int primes[MAX_SUM_OF_SQUARES+1];


template<typename T>
void printContainer(T container)
{
	cout << "( ";
	copy(container.begin(), container.end(), ostream_iterator<int>(cout, ","));
	cout << " )" << endl;
}

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

bool isPrime(int num)
{
	return (num <= MAX_SUM_OF_SQUARES && primes[num] == 1)?true:false;
}

void buildPrimeVector(vector<int> &primeVec)
{
	primeVec.clear();
	primeVec.push_back(2);
	for(int num = 3; num < MAX_SUM_OF_DIGITS; num+=2)
	{
		if(isPrime(num))
			primeVec.push_back(num);
	}
}

