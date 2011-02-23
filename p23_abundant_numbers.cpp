#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>

using namespace std;

int sum_of_divisors(int n) {
	int sum = 1;
	int store_n = n;
	
	for(int i = 2; i*i <= n && n > 1; i+=2) {
		if(n % i == 0) {
			
			n = n/i;
			int j = (i*i);
			
			while(n%i == 0) {
				n = n/i;
				j *= i;
			}			
			
			j = (j-1)/(i-1);
			sum *= j;
		}
	
		if(i == 2) i--;
	}
	
	// 1 prime remains 
	if(n > 1)
		sum *= (n+1);

	return (sum-store_n); // for sum of proper divisors subtract n
}


vector<bool> build_sum_of_abundant_numbers(int n) {
	bool *abundant_numbers = new bool[n];
	vector<bool> sum_of_abundant_numbers(n, false);
	
	for(int i = 0; i < 11 && i < n; i++)
		abundant_numbers[i] = false;
	
	for(int i = 11; i < n; i++) {
		abundant_numbers[i] = (sum_of_divisors(i+1) > (i+1)) ? true : false;
		if(abundant_numbers[i]) {
			for(int j = 11; j <= i; j++){
				if(abundant_numbers[j] && (i+j+1) < n)
					sum_of_abundant_numbers[i+j+1] = true;
			}
		}
	}
		
	return sum_of_abundant_numbers;
}

int main(int argc, char **argv) {
	int sum = 23*24/2; // 24 is the smallest number that 
					// can be written as sum of 2 abundant numbers
	int N = 28123;
	vector<bool> sum_of_abundant_numbers = build_sum_of_abundant_numbers(N);
	for(int i = 24; i < N; i++) {
		if(!sum_of_abundant_numbers[i])
			sum += (i+1);
	}
	
	cout << sum << endl;

	return 0;
}