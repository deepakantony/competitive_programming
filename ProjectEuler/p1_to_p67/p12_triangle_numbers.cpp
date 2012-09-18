#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <map>
#include <bitset>

using std::cout;
using std::endl;
using std::vector;
using std::map;
using std::bitset;


long nth_triangle(long n) {
	return n*(n+1)/2;
}

bool is_prime(long n) {
	if(n == 1) return false;
	if(n <= 3) return true;
	if(n%2 == 0 || n%3 == 0) return false;
	if(n == 5 || n == 7) return true;
	if(n <= 10) return false;
	
	long sqrt_n = floor(sqrt(n));
	for(int i = 5; i <= sqrt_n; i+=6) {
		if(n%i == 0) return false;
		if(n%(i+2) == 0) return false;
	}
	
	return true;
}

vector<int> all_primes() {
	int limit = 30000;
	
	vector<int> res;
	res.push_back(2);
	res.push_back(3);
	
	for(int i = 5; i <= limit; i+=6) {
		if(is_prime(i))
			res.push_back(i);
		if(is_prime(i+2))
			res.push_back(i+2);
	}
	
	return res;
}

int number_of_factors(long n, const vector<int> &primes) {
	if(n == 1) return 1;
	
	int n_of_factors = 1;
	long n1 = n;
	
	for(vector<int>::const_iterator it = primes.begin(); n1 > 1 && it != primes.end(); it++) {
		int exp = 1;
		while(n1 > 1 && n1%(*it) == 0) {
			n1 = n1/(*it);
			exp++;
		}
		
		if(n%(*it) == 0) {
			//cout << *it << " " << exp << endl;
			n_of_factors *= exp;
		}
	}
	
	return n_of_factors;
}

int number_of_factors(long n) {
	if(n == 1) return 1;

	map<long, long> factors_multipliers;
	
	long half_n = floor(n/2);
	
	for(long i = 2; i <= half_n && n%i == 0; i *= 2)
		factors_multipliers[2]++;
	
	for(long i = 3; i <= half_n && n%i == 0; i *= 3)
		factors_multipliers[3]++;
		
	for(long i = 5; i <= half_n; i += 6) {
		if(is_prime(i))
			for(long j = i; j <= half_n && n%j == 0; j *= i)
				factors_multipliers[i]++;
		if(is_prime(i+2))
			for(long j = i+2; j <= half_n && n%j == 0; j *= (i+2))
				factors_multipliers[i+2]++;
	}
	
	int n_of_factors = 1;
	
	//cout << "[";
	for(map<long, long>::const_iterator it = factors_multipliers.begin();
		it != factors_multipliers.end(); it++) {
		n_of_factors *= (it->second + 1);
		//cout << "(" << it->first << ", " << it->second << ")";
	}
	//cout << "]" << endl;
		
	return n_of_factors;
}
		
	
vector<long> factors(long n) {
	vector<long> fac;
	
	// add 1; 1 divides everything
	fac.push_back(1);
	
	if(n == 1) return fac;
	
	// check for all even divisors
	
	
	for(long i = 2; i <= (n/2); i++)
		if( n%i == 0)
			fac.push_back(i);
		
	// add n; n divides itself
	fac.push_back(n);
	
	return fac;
}

long first_triangle_with_n_divisors(long n) {
	long i = 1;
	long div = 1;
	long nth_tri = 1;
	vector<int> primes = all_primes();
	while( div <= n ) {
		//nth_tri = nth_triangle(i);
		if(i%2 == 0)
			div = number_of_factors(i/2, primes) * number_of_factors(i+1, primes);
		else
			div = number_of_factors(i, primes) * number_of_factors((i+1)/2, primes);
		i++;
	}
	return i*(i-1)/2;
}

int main(int argc, char *argv[]) {
	cout << first_triangle_with_n_divisors(atoi(argv[1])) << endl;
	
	//cout << number_of_factors(atoi(argv[1]), all_primes()) << endl;

	return 0;
}
