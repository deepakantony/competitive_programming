#include <iostream>
#include <cstdlib>
#include <vector>
#include <bitset>
#include <cmath>

using namespace std;

template<size_t N>
void build_primes(bitset<N> &is_prime, vector<int> &all_primes) {
	// 2 and 3
	is_prime.set(2);
	all_primes.push_back(2);
	is_prime.set(3);
	all_primes.push_back(3);
	for(int i = 5; i <= N; i+=2) {
		for(int k = 0; k < 2; k++) {
			int sqrt_i = ceil(sqrt(i));
			bool prime = true;
			for(int j = 5; j <= sqrt_i; j+=6) {
				if(i%j == 0) prime = false;
				if(i%(j+2) == 0) prime = false;
			}
			if(prime) {
				is_prime.set(i);
				all_primes.push_back(i);
			}
			i += 2;
		}
	}	
}

template<size_t N>
bool is_circle_prime(int num, const bitset<N> &is_prime) {
	int multiply_by = 1;
	int num_temp = num;
	while(num_temp > 0) {
		num_temp /= 10;
		multiply_by *= 10;
	}
	multiply_by /= 10;
	
	int num_rotate = num;
	do {
		if(!is_prime.test(num_rotate)) return false;
		int last_dig = num_rotate%10;
		num_rotate /= 10;
		num_rotate += last_dig*multiply_by;
	} while(num_rotate != num);
	
	return true;
}

template<size_t N>
int count_of_circular_primes() {
	bitset<N> is_prime;
	vector<int> all_primes;
	build_primes(is_prime, all_primes);
	
	int count = 0;
	for(vector<int>::const_iterator it = all_primes.begin(); it != all_primes.end(); it++) {
		if(is_circle_prime(*it, is_prime))
			count++;
	}
	return count;
}

int main(int argc, char **argv) {
	cout << count_of_circular_primes<1000000> () << endl;
	return 0;
}
	