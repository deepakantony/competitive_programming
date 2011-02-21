#include <iostream>

using namespace std;



bool is_sum_of_2_abundant(int n) {
	int n_half = floor(n/2);
	for(int i = 12; i <= n_half; i++)
		for(int j = n_half; j < n && (i+j) <= n; j++)
			if(is_abundant(i) && is_abundant(j) && (i+j) == n)
				return true;
	return false;
}

int main(int argc, char **argv) {
	int sum = 23*24/2; // 24 is the smallest number that 
					// can be written as sum of 2 abundant numbers
	
	for(int i = 25; i <= 28123; i++) {
		if(is_sum_of_2_abundant(i))
			sum += i;
	}
	
	cout << sum << endl;

	return 0;
}
