#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>

using namespace std;


string sum(string num1, string num2) {
	if(num2.size() > num1.size()) 
		swap(num1, num2);
		
	char carry = 0;
	string::reverse_iterator num1_it = num1.rbegin();
	string::reverse_iterator num2_it = num2.rbegin();
	string sum;
	while(num1_it != num1.rend()) {
		char s = carry + (*num1_it - '0');
		if(num2_it != num2.rend()) {
			s += (*num2_it - '0');
			num2_it++;
		}
		carry = s/10;
		sum += (s%10 + '0');
		
		num1_it++;
	}
	
	if(carry > 0)
		sum += (carry + '0');
	
	reverse(sum.begin(), sum.end());
	
	return sum;
}

long long int fibo_first_num_with_n_digits(int n, string &c) {
	if(n == 1) return 1l;
	
	string a = "1";
	string b = "1";
	long long int term = 2l;
	do {
		c = sum(a, b);
		a = b;
		b = c;
		term++;
	} while(c.size() < n);
	
	return term;
}

int main(int argc, char **argv) {
	string num;
	cout << fibo_first_num_with_n_digits(atoi(argv[1]), num) << endl;
	cout << num << endl;
	
	return 0;
}

