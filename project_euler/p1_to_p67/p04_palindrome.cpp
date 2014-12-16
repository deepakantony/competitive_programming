#include <iostream>
#include <cmath>
#include <inttypes.h>

using std::cout;
using std::endl;

int length(long n) {
	int len = 0;
	while(n > 0) {
		n = n / 10;
		len++;
	}
	
	return len;
}

long reverse(long n) {
	long rev = 0;
	
	while(n > 0) {
		int digit = n % 10;
		rev = rev * 10 + digit;
		n = n / 10;
	}
		
	return rev;
}

bool is_palindrome(long n) {
	return (n == reverse(n));
}

int main(int argc, char* argv[]) {
    long lowest = 100 * 100;
	long highest = 999 * 999;
	
	long factor1 = 0;
	long factor2 = 0;
	
	long highest_palindrome = 0;
	
	for(long i = highest; i >= lowest; i--) {
		if(is_palindrome(i)) {
			for(long j = 999; j >= 100; j--) {
				if(i % j == 0) {
					long k = i / j;
					
					if( length(k) == 3 ) {
						factor1 = j;
						factor2 = k;
						highest_palindrome = i;
						
						break;
					}						
				}
			}
		}
		if(highest_palindrome != 0)
			break;
	}

    cout << highest_palindrome << endl;
	cout << factor1 << " " << factor2 << endl;

    return 0;
}
