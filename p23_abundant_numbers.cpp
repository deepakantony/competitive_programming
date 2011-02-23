#include <iostream>
#include <cstdlib>

using namespace std;

int sum_of_divisors(int n) {
	int sum = 1;
	
	for(int i = 2; i*i > n && n > 1; i+=2) {
		
	}
	
	// 1 prime remains 
	if(n > 1)
		sum *= (n+1);
	

	return (sum-n); // for sum of proper divisors subtract n
}

bool* build_abundant_numbers(int n) {
	bool *abundant_numbers = (bool*)malloc(n*sizeof(bool));
	for(int i = 0; i < 12 && i < n; i++)
		abundant_numbers[i] = false;
	
	for(int i = 12; i < n; i++)
		abundant_numbers[i] = (sum_of_divisors(i) > i) ? true : false;
		
	return abundant_numbers;
}

bool is_sum_of_2_abundant(int n, const bool* abundant_numbers) {
	int n_half = floor(n/2);
	for(int i = 12; i <= n_half; i++)
		for(int j = n_half; j < n && (i+j) <= n; j++)
			if(abundant_numbers[i-1] && abundant_numbers[j-1] && (i+j) == n)
				return true;
	return false;
}

int main(int argc, char **argv) {
	int sum = 23*24/2; // 24 is the smallest number that 
					// can be written as sum of 2 abundant numbers
	bool* abundant_numbers = build_abundant_numbers(28123);
	for(int i = 25; i <= 28123; i++)
		if(is_sum_of_2_abundant(i, abundant_numbers))
			sum += i;
	
	cout << sum << endl;

	return 0;
}
