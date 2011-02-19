#include <iostream>

using namespace std;

int string_number(string str) {
	string::const_iterator it = str.begin();
	int sum = 0;
	while(it != str.end()) {
		if(isalpha(*it))
			sum = sum + (tolower(*it) - 'a' + 1);
	}
	
	return sum;
}

template<class T, class Compare>
void sort(T begin, T end, Compare cmp) {

}

int sum_of_string

int main(int argc, char **argv) {
	return 0;
}
	