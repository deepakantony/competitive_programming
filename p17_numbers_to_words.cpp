#include <iostream>
#include <cstdlib>
#include <map>
#include <string>

using namespace std;

static map<int, string> number_mappings;

void build_number_mappings() {
	number_mappings[1] = string("one");
	number_mappings[2] = string("two");
	number_mappings[3] = string("three");
	number_mappings[4] = string("four");
	number_mappings[5] = string("five");
	number_mappings[6] = string("six");
	number_mappings[7] = string("seven");
	number_mappings[8] = string("eight");
	number_mappings[9] = string("nine");
	number_mappings[10] = string("ten");
	number_mappings[11] = string("eleven");
	number_mappings[12] = string("twelve");
	number_mappings[13] = string("thirteen");
	number_mappings[14] = string("fourteen");
	number_mappings[15] = string("fifteen");
	number_mappings[16] = string("sixteen");
	number_mappings[17] = string("seventeen");
	number_mappings[18] = string("eighteen");
	number_mappings[19] = string("nineteen");
	number_mappings[20] = string("twenty");
	number_mappings[30] = string("thirty");
	number_mappings[40] = string("forty");
	number_mappings[50] = string("fifty");
	number_mappings[60] = string("sixty");
	number_mappings[70] = string("seventy");
	number_mappings[80] = string("eighty");
	number_mappings[90] = string("ninety");
	number_mappings[100] = string("hundred");
	number_mappings[1000] = string("thousand");
	number_mappings[1000000] = string("million");
}

string number_to_words(int n) {
	string word;
	
	if(n <= 20) return number_mappings[n];
	
	if(n < 100) {
		if(n%10 == 0) return number_mappings[n];
		word = number_mappings[n-(n%10)] + " " + number_mappings[n%10];
	}
	else if(n < 1000) {
		if(n%100 == 0) {
			word = number_mappings[n/100] + " " + number_mappings[100];
		}
		else {
			word = number_mappings[n/100] + " " + number_mappings[100] + " and "
					+ number_to_words(n%100);
		}
	}
	else if(n < 1000000) {
		if(n%1000) {
			word = number_to_words(n/1000) + " " + number_mappings[1000] + " "
				+ number_to_words(n%1000);
		}
		else word = number_to_words(n/1000) + " " + number_mappings[1000];
	}
	
	return word;
}

int number_of_letters_in_numbers(int n) {
	int sum = 0;
	for(int i = 1; i <= n; i++) {
		string number = number_to_words(i);
		for(string::const_iterator it = number.begin(); it != number.end(); 
			++it) {
			if(isalpha(*it))
				sum++;
		}
	}
	
	return sum;
}

int main(int argc, char *argv[]) {
	build_number_mappings();
	cout << number_of_letters_in_numbers(atoi(argv[1])) << endl;
	
	return 0;
}
