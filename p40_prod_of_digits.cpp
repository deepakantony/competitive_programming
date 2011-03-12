#include <iostream>
#include <cstdlib>

using namespace std;

int reverse(int n) {
	int rev = 0;
	while(n > 0) {
		rev = rev*10 + n%10;
		n /= 10;
	}
	return rev;
}

int d(int n) {
	int base_cur = 1;
	int base_next = 10;
	int cur_digits = 1;
	int base_digits = 1;
	int prev_base_digits = 1;

	while(base_digits < n) {
		prev_base_digits = base_digits;
		base_digits += (cur_digits*(base_next-base_cur));
		cur_digits++;
		base_cur *= 10;
		base_next *= 100;
	}
	if(base_digits == n) return 1;
	cur_digits--;
	base_cur /= 10;
	base_next /= 10;
	
	int remaining_digits = n - prev_base_digits + 1;
	
	int the_number = base_cur + remaining_digits/cur_digits;
	
	if(remaining_digits%cur_digits == 0) return (the_number-1)%10;
	
	the_number = reverse(the_number);
	int digit = -1;
	for(int i = remaining_digits%cur_digits; i > 0; i--) {
		digit = the_number%10;
		the_number /= 10;
	}
	return digit;
}

string to_string(int n) {
	string n_str;
	while(n>0){
		n_str += n%10;
		n /= 10;
	}
	reverse(n_str.begin(), n_str.end());
	return n_str;
}

int d2(int n) {
	
}

int main(int argc, char **argv) {
	//cout << d(1)*d(10)*d(100)*d(1000)*d(10000)*d(100000)*d(1000000) << endl;
	cout << d(atoi(argv[1])) << endl;
	return 0;
}
