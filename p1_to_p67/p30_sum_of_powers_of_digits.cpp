#include <iostream>
#include <climits>
#include <cstdlib>

using namespace std;

int int_pow(int a, int b) {
	int pow_ab = 1;
	for(int i = 0; i < b; i++)
		pow_ab *= a;
	return pow_ab;
}

long int sum_of_digits_to_the_power_of(long int n, int power) {
	long int sum = 0l;
	while(n > 0) {
		sum += int_pow(n%10, power);
		n = n/10;
	}
	return sum;
}

unsigned long int sum_of_powers_digits(int power) {
	unsigned long int sum = 0l;
	unsigned long int pow_9 = int_pow(9, power);
	unsigned long int limit = pow_9;
	unsigned long int smallest = 1;
	while(smallest < limit) {
		smallest *= 10;
		limit += pow_9;
	}
	
	limit = smallest - 1;
	cout << limit << endl;
	
	for(long int i = 2; i <= limit; i++) {
		if(sum_of_digits_to_the_power_of(i,power) == i)
			sum += i;
			
		//cout << i << endl;
	}
	return sum;
}

int main(int argc, char **argv){
	cout << sum_of_powers_digits(atoi(argv[1])) << endl;
	return 0;
}
	