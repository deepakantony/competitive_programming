#include <iostream>
#include <cmath>

using namespace std;

bool is_prime(int n) {
	if(n == 2 || n == 3 || n == 5 || n == 7) return true;
	if(n%2 == 0 || n%3 == 0) return false;
	int sqrt_n = ceil(sqrt(n));
	for(int i = 5; i <= sqrt_n; i+=6) {
		if(n%i == 0) return false;
		if(n%(i+2) == 0) return false;
	}
	return true;
}

int reverse(int n) {
	int rev = 0;
	while(n > 0) {
		rev = rev*10 + (n%10);
		n /= 10;
	}
	return rev;
}

bool is_trancatable_prime(int n) {
	n = reverse(n)/10;
	while(n > 0) {
		if(!is_prime(reverse(n))) return false;
		n /= 10;
	}
	return true;
}


void find_sum(int n, int &sum) {
	int cur = n*10+1;
	if(is_prime(cur))
		find_sum(cur, sum);
	cur = n*10+3;
	if(is_prime(cur)) {	
		if(is_trancatable_prime(cur)) {
			sum += cur;
			cout << cur << endl;
		}
		find_sum(cur, sum);
	}
	cur = n*10+7;
	if(is_prime(cur)) {
		if(is_trancatable_prime(cur)) {
			sum += cur;
			cout << cur << endl;
		}
		find_sum(cur, sum);
	}
	cur = n*10+9;
	if(is_prime(cur))
		find_sum(cur, sum);
}

int sum_of_truncatable_primes() {
	int sum = 0;
	find_sum(3, sum);
	find_sum(7, sum);
	find_sum(5, sum);
	find_sum(2, sum);
	return sum;
}

int main(int argc, char **argv) {
	cout << sum_of_truncatable_primes() << endl;
	return 0;
}