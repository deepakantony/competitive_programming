#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <cmath>

using namespace std;

string repeating_decimal(int n) {	
	// store remainders
	vector<int> remainders;
	// storing remainder in map also for fast search
	map<int, bool> remainders_map;
	
	// store quotients
	string quotients;
	
	int remainder = 10;
	
	while(remainder > 0 
		&& remainders_map.find(remainder) == remainders_map.end()) {
		remainders.push_back(remainder);
		remainders_map[remainder] = true;
		
		while(n > remainder) {
			remainder *= 10;
			remainders.push_back(remainder);
			remainders_map[remainder] = true;
			quotients += '0';
		}
		
		quotients += ((char)(remainder/n) + '0');
		remainder %= n;
		remainder *= 10;
	}
	
	if(remainder == 0) return string("");
	
	int idx = 0;
	for(vector<int>::const_iterator it = remainders.begin();
		it != remainders.begin() && *it != remainder; it++, idx++)
		{}
	
	return string(quotients.begin()+idx, quotients.end());
}

bool is_prime(int n) {
	if(n == 1) return false;
	if(n < 4) return true;
	if(n%2 == 0 || n%3 == 0) return false;
	if(n < 11) return true;
	int sqrt_n = ceil(sqrt(n));
	for(int i = 11; i < sqrt_n; i+=4) {
		if(n%i == 0) return false;
		i += 2;
		if(n%i == 0) return false;
	}
	return true;
}

int largest_repeating_decimal(int n) {
	if(n < 2) return 0;
	
	int largest = 1;
	int largest_repeatend = 0;
	for(int denom = 2; denom < n; denom++) {
		if(is_prime(denom)) {
			int repeatend = repeating_decimal(denom).size();
			if( repeatend > largest_repeatend ) {
				largest_repeatend = repeatend;
				largest = denom;
			}
		}
	}
	
	return largest;
}

int main(int argc, char **argv) {
	cout << largest_repeating_decimal(atoi(argv[1])) << endl;

	return 0;
}
