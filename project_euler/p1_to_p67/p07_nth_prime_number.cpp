#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>

using std::cout;
using std::endl;
using std::vector;

int nth_prime(int n) {
	if(n == 1)
		return 2;
		
	vector<int> primes;
	
	primes.push_back(2); // already checked for 2
	int i = 3; // start from 3	
	while(primes.size() < n) {
		int sqrt_i = floor(sqrt(i));
		bool is_prime = true;
		for(vector<int>::const_iterator it = primes.begin(); 
			it != primes.end() && (*it) <= sqrt_i; ++it)
			if(i % (*it) == 0) {
				is_prime = false;
				break;
			}
		if(is_prime)
			primes.push_back(i);
		
		i += 2;
	}
	
	return primes[n-1];
}
	

int main(int argc, char *argv[]) {
	int n = atoi(argv[1]);
	
	cout << nth_prime(n) << endl;
	
	return 0;
}
