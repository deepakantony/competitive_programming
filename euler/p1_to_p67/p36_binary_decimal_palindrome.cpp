#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

bool is_palindrome(string str) {
	string::const_iterator left = str.begin();
	string::const_iterator right = str.end()-1;
	
	while(left < right) {
		if(*left != *right) return false;
		left++; right--;
	}
	return true;
}

string to_string(int n) {
	string str;
	while(n>0) {
		str += (((char)(n%10)) + '0');
		n /= 10;
	}
	return str;
}

string to_binary_string(int n) {
	string binary;
	while(n > 0) {
		binary += (((char)(n%2)) + '0');
		n = n/2;
	}
	reverse(binary.begin(), binary.end());
	return binary;
}

int sum_of_double_palindromes(int n) {
	int sum = 0;
	for(int i = 1; i < n; i++)
		if(is_palindrome(to_string(i)) && is_palindrome(to_binary_string(i)))
			sum += i;

	return sum;
}

int main(int argc, char **argv) {
	cout << sum_of_double_palindromes(atoi(argv[1])) << endl;
	
	//cout << to_string(atoi(argv[1])) << endl;
	//cout << to_binary_string(atoi(argv[1])) << endl;
	
	return 0;
}
