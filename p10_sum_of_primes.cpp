#include <iostream>
#include <cstdlib>
#include <cmath>

using std::cout;
using std::endl;

bool is_prime(long n) {
	if(n <= 1) 
		return false;
	if(n <= 3) // if 2 or 3
		return true;
	if(n%2 == 0)
		return false;
	if(n%3 == 0)
		return false;
	if(n == 5 && n == 7) // if 5 or 7
		return true;
	
	long sqrt_n = floor(sqrt(n));
	// now for primes > 3 they're of the form 6k +/- 1
	// starting with k = 1
	for(long x = 5; x <= sqrt_n; x+=6) {
		// if divisible by 6k-1
		if(n%x == 0) return false;
		// if divisible by 6k+1
		if(n%(x+2) == 0) return false;
	}
	
	// its a prime!
	return true;
}

long long find_sum_primes_below(long n) {
	if(n <= 2) return 0ll;
	
	// start from 2
	long long sum = 2ll;
	
	if(n == 3) return sum;
	
	// add 3 to the sum
	sum += 3ll;
	
	if(n == 5) return sum;
	
	for(long x = 5; x < n; x+=6) {
		if(is_prime(x))
			sum += x;
		if(is_prime(x+2))
			sum += (x+2);
	}
	
	return sum;
}

int main(int argc, char *argv[]) {
	long n = atol(argv[1]);
	
	cout << find_sum_primes_below(n) << endl;
	
	return 0;
}
	