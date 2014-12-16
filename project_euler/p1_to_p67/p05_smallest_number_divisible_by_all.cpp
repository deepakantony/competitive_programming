#include <iostream>
#include <vector>
#include <cmath>

using std::cout;
using std::endl;
using std::vector;

// find prime numbers till N
vector<int> primes(int n) {
	vector<int> p;
	
	// add 2 and we can skip all even numbers!
	if(n > 1)
		p.push_back(2);

	for(int i = 3; i <= n; i+=2) {
		int sqrt_i = floor(sqrt(i));
		
		bool is_prime = true;
		for(vector<int>::const_iterator iter = p.begin(); iter != p.end() && (*iter) <= sqrt_i; iter++)
			if( i % (*iter) == 0 )
				is_prime = false;
		if(is_prime)
			p.push_back(i);
	}
	
	return p;
}

void print_vector(const vector<int> &vec) {
	cout << "(";
	for(vector<int>::const_iterator iter = vec.begin(); iter != vec.end(); iter++)
		cout << (*iter) << " ";
	cout << ")";
}

int main(int argc, char* argv[]) {
	int n = 20;
	vector<int> prime_numbers = primes(n);
	vector<int> multipliers(prime_numbers.size(), 1);
	int sqrt_n = floor(sqrt(n));
	long final_result = 1;
	for(int i = 0; i < prime_numbers.size(); i++)
		if( prime_numbers[i] < sqrt_n )
			final_result *= pow(prime_numbers[i], floor(log(n)/log(prime_numbers[i])));
		else
			final_result *= prime_numbers[i];
	
	cout << final_result << endl;
	
	long largest_number = 16*9*5*7*11*13*17*19;

	cout << largest_number << endl;

	return 0;
}