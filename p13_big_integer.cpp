#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using std::cout;
using std::endl;
using std::ifstream;
using std::string;

class BigInteger {
public:
	BigInteger(string number);
	BigInteger(const char*);
	BigInteger();

	BigInteger operator+(BigInteger &num) ;
	string to_string() const;

private:
	string _number;
};

BigInteger::BigInteger(string number) {
	this->_number = number;
}

BigInteger::BigInteger(const char *number) {
	this->_number = string(number);
}

BigInteger::BigInteger() {
	this->_number = string("0");
}

BigInteger BigInteger::operator+(BigInteger &num) {
	string result;
	string::reverse_iterator small_number;
	string::reverse_iterator large_number;
	string::reverse_iterator small_end;
	string::reverse_iterator large_end;	
	
	
	if(this->_number.size() > num._number.size()) {
		large_number = this->_number.rbegin();
		small_number = num._number.rbegin();
		large_end = this->_number.rend();
		small_end = num._number.rend();
	}
	else {
		small_number = this->_number.rbegin();
		large_number = num._number.rbegin();
		small_end = this->_number.rend();
		large_end = num._number.rend();
	}
	
	char carry = 0;
	while(large_number < large_end) {
		char sum = (*large_number) - '0';
		if(small_number < small_end) {
			sum += ((*small_number) - '0');
			small_number++;
		}
		sum += carry;
		carry = sum/10;
		result += ((sum%10) + '0');
		large_number++;
	}
	
	if( carry > 0 )
		result += (carry + '0');
	
	reverse(result.begin(), result.end());
	
	return BigInteger(result);
}

string BigInteger::to_string() const {
	return this->_number;
}

int main(int argc, char *argv[]) {
	ifstream file_of_large_numbers;
	file_of_large_numbers.open(argv[1]);
	char num[1000];
	BigInteger sum("0");
	while(file_of_large_numbers.getline(num, 1000)) {
		BigInteger n(num);
		sum = sum + n;
	}
	
	cout << sum.to_string() << endl;
	
	return 0;
}