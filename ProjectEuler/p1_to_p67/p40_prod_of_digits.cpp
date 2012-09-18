#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>

using namespace std;

string to_string(int n) {
	string rev;
	while(n > 0) {
		rev += (n%10 + '0');
		n /= 10;
	}
	reverse(rev.begin(), rev.end());
	
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
		base_next *= 10;
	}
	if(base_digits == n) return 1;
	cur_digits--;
	base_cur /= 10;
	base_next /= 10;
	
	int remaining_digits = n - prev_base_digits + 1;
	
	int the_number = base_cur + remaining_digits/cur_digits;
	
	if(remaining_digits%cur_digits == 0) return (the_number-1)%10;
	
	string str_number = to_string(the_number);
	
	return (int)(to_string(the_number)[remaining_digits%cur_digits-1]-'0');
}

int d2(int n) {
	
}

int main(int argc, char **argv) {
	cout << d(1)*d(10)*d(100)*d(1000)*d(10000)*d(100000)*d(1000000) << endl;
	return 0;
}
