#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>

using namespace std;

int compare(string num1, string num2) {
	int size1 = num1.size();
	int size2 = num2.size();
	
	if(size1 == size2) {
		for(int i = 0; i < size1; i++) {
			if(num1[i] != num2[i])
				if(num1[i] > num2[i]) return 1;
				else return -1;
		}
		return 0;
	}
	
	if(size1 > size2) return 1;
	//else
	return -1;
}

string add(string num1, string num2) {
	string sum;
	
	string ln, sn;
	if(compare(num1,num2) > 0) {
		ln = num1;
		sn = num2;
	}
	else {
		ln = num2;
		sn = num1;
	}
	
	char carry = 0;
	
	string::reverse_iterator ln_it = ln.rbegin();
	string::reverse_iterator sn_it = sn.rbegin();
	while(ln_it < ln.rend()) {
		char s = (*ln_it - '0');
		if(sn_it < sn.rend()) {
			s += (*sn_it - '0');
			++sn_it;
		}
		s += carry;
		
		sum += ((s%10) + '0');
		carry = s/10;
		
		++ln_it;
	}
	
	if(carry > 0)
		sum += (carry + '0');
		
	reverse(sum.begin(), sum.end());
	
	return sum;
}

string factorial(int n) {

	string fact = "1";
	
	for(int i = 2; i <= n; i++) {
		string cur = fact;
		for(int j = 1; j < i; j++)
			fact = add(fact, cur);
	}
	
	return fact;
}

int sum_of_digits(string num) {
	int sum = 0;
	
	string::const_iterator it = num.begin();
	while(it != num.end()) {
		sum += (*it - '0');
		++it;
	}
	
	return sum;
}


int main(int argc, char **argv) {
	string f = factorial(atoi(argv[1]));
	cout << f << endl;
	cout << sum_of_digits(f) << endl;
	cout << add(string("99"), string( "99")) << endl;

	return 0;
}
