#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>

using namespace std;

string sum(string num1, string num2) {
	string result;
	string more_digits = num1;
	string less_digits = num2;
	
	if(num2.size() > num1.size()) {
		less_digits = num1;
		more_digits = num2;
	}
	
	char carry = 0;
	
	string::reverse_iterator more_it = more_digits.rbegin();
	string::reverse_iterator less_it = less_digits.rbegin();
	while(more_it < more_digits.rend()) {
		char sum = (*more_it) - '0';
		sum += carry;
		carry = 0;
		if(less_it < less_digits.rend()) {
			sum += ((*less_it) - '0');
			less_it++;
		}
		
		carry = sum/10;
		result += ((sum%10) + '0');		
		more_it++;
	}
	
	if(carry > 0)
		result += (carry + '0');
	
	reverse(result.begin(), result.end());
	
	return result;
}

string power_of_2(int power) {
	if(power == 0) return "1";

	string result = "2";
	
	for(int i = 1; i < power; i++) {
		result = sum(result, result);
		cout << result << " ";
	}
	
	return result;
}

long long int sum_of_digits(string num) {
	string::const_iterator it = num.begin();
	long long int result = 0;
		
	while(it != num.end()) {
		result += ((*it) - '0');
		it++;
	}
	
	return result;
}

int main(int argc, char *argv[]) {
	string power2 = power_of_2(atoi(argv[1]));
	cout << power2 << endl;
	cout << endl << sum_of_digits(power2) << endl;
	return 0;
}
