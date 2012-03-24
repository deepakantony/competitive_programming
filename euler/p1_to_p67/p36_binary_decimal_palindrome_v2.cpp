#include <iostream>
#include <cstdlib>

using namespace std;

bool is_palindrome(int n, int base) {
	int reverse = 0;
	int num = n;
	while(num > 0) {
		reverse = reverse*base + num%base;
		num /= base;
	}
	
	return (n == reverse);
}

unsigned generate_palindrome_base2(unsigned n, bool oddlength) {
	unsigned res = n;
	if(oddlength) n >>= 1;
	while(n > 0) {
		res = (res << 1) + (n&1);
		n >>= 1;
	}
	return res;
}

int sum_2base_palindromes(int n) {
	int p;
	int sum = 0;
	for(int k = 0; k < 2; k++) 
		for(int i = 1; (p = generate_palindrome_base2(i, !k)) < n; i++) {
			if(is_palindrome(p, 10)) sum += p;
		}
	return sum;
}

int main(int argc, char **argv) {
	cout << sum_2base_palindromes(atoi(argv[1])) << endl;
	return 0;
}
