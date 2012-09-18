#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

bool is_prime(int n) {
	if(n <= 1) return false;
	if(n < 4) return true;
	if(n%2 == 0 || n%3 == 0) return false;
	if(n < 11) return true;
	int sqrt_n = ceil(sqrt(n));
	for(int i = 11; i < sqrt_n; i+=6) {
		if(n%i == 0) return false;
		if(n%(i+2) == 0) return false;
	}
	return true;
}

void find_a_b(int &a, int &b) {
	a = 1; b = 41;
	int largest = 40;
	
	for(int i = -999; i < 1000; i++) {
		for(int j = 2; j < 1000; j++) {
			if(is_prime(j)){
				int n = 1;
				while(is_prime(n*n + n*i + j))
					n++;
					
				if(n > largest) {
					largest = n;
					a = i;
					b = j;
				}
			}
		}
	}
}


int main(int argc, char **argv) {

	int a, b;
	find_a_b(a,b);
	cout << a*b << endl;

	return 0;
}
