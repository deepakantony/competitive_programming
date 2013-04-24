// EQUATIONS - problem description
//  
// Find the no of positive integral solutions for the equations 
// (1/x) + (1/y) = 1/N! (read 1 by n factorial) 
// Print a single integer which is the no of positive integral solutions
// modulo 1000007.
// 
// 	Input:
// N 
// 	Output:
// 	Number of positive integral solutions for (x,y) modulo 1000007
// 														Constraints:
// 1 <= N <= 10^6 
// 	Sample Input00:
// 1
// 	Sample Output00:
// 1
//  
// 	Sample Input01:
// 32327
// 	Sample Output 01:
// 656502
//  
// 	Sample Input02:
// 40921
// 	Sample Output 02:
// 686720
//  


// This is a number theory problem.
// First we should know how to calculate the number of +integer solutions for
// 1/x + 1/y = 1/n  (note n is not factorial; this is any number)
// Given n = (p1^e1)*(p2^e2)*...*(pk^ek) prime factorization of n
// the number of solutions for the initial equation is
// (2*e1 + 1)*(2*e2 + 1)*...*(2*ek + 1)
// See the proof from the paper http://www.artofproblemsolving.com/Resources/Papers/SatoNT.pdf
// section 3 - example 3.1
//
// Now, we need to find prime factorization of N! for the main problem.
// For this, there is a clean description I found 
// @ http://answers.yahoo.com/question/index?qid=20091027134709AAVJlxi
// ******* This is copied from the above location
// Let me try to do 40! first, and then say something about the more general 
// case. Obviously the prime factorization of 40! only contains primes less 
// than 40- the question is what the power of each should be. The primes 
// less than 40 are:
// 
// 2,3,5,7,11,13,17,19,23,29,31,37.
// 
// How many factors of say 2 are there in 40! ? First of all, the number 
// of numbers less than or equal to 40 that have a factor of 2 is:
// 
// floor(40/2) = 20.
// 
// (Here floor(x) means round to the largest integer smaller than x). Of 
// course some of them have more than one factor of 2. How many of them 
// have at least two factors of 2? Every other one does so it's:
// 
// floor(20/2) = 10.
// 
// How many of them have 3 factors of 2?
// 
// floor(10/2) = 5.
// 
// 4 factors of 2?
// 
// floor(5/2) = 2.
// 
// 5 factors of 2?
// 
// floor(2/2) = 1.
// 
// So the total number of factors of 2 is:
// 
// 20+10+5+2+1 = 38.
// 
// Similarly, you could find the number of factors of 3 as
// 
// floor(40/3) + floor(13/3) + floor(4/3) = 13 + 4 + 1 = 18.
// 
// Doing the rest:
// 
// floor(40/5) + floor(8/5) = 8 + 1 = 9,
// floor(40/7) = 5,
// floor(40/11) = 3,
// floor(40/13) = 3,
// floor(40/17) = 2,
// floor(40/19) = 2,
// 
// and the rest are 1. So the prime factorization is
// 
// 40! = 2^{38} 3^{18} 5^{9} 7^{5} 11^{3} 13^3 17^2 19^2 23 29 31 37.
// 
// You can write the calculation for the exponent of the prime p in the more 
// compact form
// 
// sum_{i=1}^{floor(log_p(40)} floor(40/p^i).
// 
// That's a sum from 1 to log base p of 40. A similar formula would allow 
// you to write a formula for the prime factorization of n! for general n.
//  I don't know if there's a simpler way ... .


#include <iostream>
#include <bitset>
#include <cmath>

using namespace std;

#define PRIME_SIZE 1000001
#define MOD_NUM 1000007l

void sieve(bitset<PRIME_SIZE> &primes)
{
	primes.set(); // set all numbers as prime first

	primes.reset(0); // reset 0
	primes.reset(1);

	int sqrtSize = floor(sqrt(PRIME_SIZE-1));

	for(int index = 2; index < sqrtSize; index++)
		for(int nonPrimes = 2; nonPrimes * index < PRIME_SIZE; nonPrimes++)
			primes.reset(nonPrimes * index);
}

// find the number of positive integers solutions to the eq 1/x + 1/y = 1/N!
// since this is large number, return sols % 1000007
long long numberOfSols(int N, const bitset<PRIME_SIZE> &primes)
{
	if( N == 1 )
		return 1;

	long long  nSols = 1;
	for(int prime = 2; prime <= N; prime++)
	{
		if(primes[prime])
		{

			long long primePower = 0;
			long long tempN = N;
			while(tempN >= prime)
			{
				tempN = floor(tempN/prime);
				primePower = (primePower+tempN)%MOD_NUM;
			}
//			cout << prime << "^" << primePower << endl;
			nSols = (nSols * ((2l*primePower+1)%MOD_NUM))%MOD_NUM;
		}
	}

	// (a*b)%c = ((a%c)*(b%c))%c
	return nSols%MOD_NUM;
}

int main(int argc, char *argv[])
{
	bitset<PRIME_SIZE> primes;
	sieve(primes);

	int N;
	cin >> N;
	cout << numberOfSols(N, primes) << endl;

	return 0;
}

