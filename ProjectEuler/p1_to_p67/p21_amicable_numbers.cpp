#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>

using namespace std;


vector<int> proper_divisors(int n) {
	vector<int> divs;
	divs.push_back(1); // 1 divides everything
	int sqrt_n = ceil(sqrt(n));
	for(int i = 2; i < sqrt_n; i++) {
		if(n%i == 0) {
			divs.push_back(i);
			divs.push_back(n/i);
		}
	}
	if(sqrt_n * sqrt_n == n) {
		divs.erase(divs.begin() + divs.size() - 1);
	}
	
	//sort(divs.begin(), divs.end());
	
	return divs;
}

template< class T > 
int sum(T begin, T end) {
	int s = 0;
	for(T it = begin; it != end; it++)
		s += *it;
	return s;
}

int sum_of_divisors(int n) {
	vector<int> divs = proper_divisors(n);
	
	return sum(divs.begin(), divs.end());
}

vector<int> construct_divisors_sum_till_n(int n) {
	vector<int> divisors;
	
	divisors.push_back(0); // for 0
	divisors.push_back(0); // for 1
	
	for(int i = 2; i < n; i++)
		divisors.push_back(sum_of_divisors(i));

	return divisors;
}

int sum_of_amicable_numbers(int n) {
	int sum = 0;
	
	vector<int> divisors_sum = construct_divisors_sum_till_n(n);
	for(int i = 1; i < n; i++)
		if( (divisors_sum[i] < n) && (i < divisors_sum[i]) && 
			(i == divisors_sum[divisors_sum[i]]) ) {
			sum += (i + divisors_sum[i]);
			cout << i << " " << divisors_sum[i] << endl;
		}
	
	return sum;
}

int main(int argc, char**argv) {
	cout << sum_of_amicable_numbers(atoi(argv[1]));

	return 0;
}
