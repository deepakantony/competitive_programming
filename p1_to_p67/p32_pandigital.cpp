#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

int to_int(string::const_iterator begin, string::const_iterator end) {
	int num = 0;
	for(string::const_iterator it = begin; it != end; it++) {
		num = num*10 + (*it - '0');
	}
	
	return num;
}

vector<int> product_pandigital(string num) {
	int equals_loc = 5; // you gain speed if you use this value
						// but the function will not be generic
	vector<int> products;
	
	for(int star_loc = 1; star_loc < num.size()-2; star_loc++)
		for(int equals_loc = star_loc+1; equals_loc < num.size()-1; equals_loc++) {
			int multiplicand = to_int(num.begin(), num.begin()+star_loc);
			int multiplier = to_int(num.begin()+star_loc, num.begin()+equals_loc);
			int product = to_int(num.begin()+equals_loc, num.end());
			if(multiplicand*multiplier == product)
				products.push_back(product);
		}
	return products;
}

template<class T>
bool next_perm(T start, T end) {
	T pos = start;
	for(T it = start; (it+1) != end; it++)
		if(*it < *(it+1))
			pos = it;
			
	if(*pos > *(pos+1)) return false;
	
	T swap_pos = pos+1;
	for(T it = pos+2; it != end; it++)
		if(*it > *pos)
			swap_pos = it;
			
	iter_swap(pos, swap_pos);
	reverse(pos+1, end);
	
	return true;
}

int lexicograph_pandigital_sum(int n) {
	map<int, int> product_map;
	
	string num;
	char endc = (char)n + '0';
	for(char c = '1'; c <= endc; c++)
		num += c;
	
	int sum = 0;
	do {
		vector<int> products = product_pandigital(num);
		for(vector<int>::const_iterator it = products.begin(); it != products.end(); it++) {
			product_map[*it]++;
			if(product_map[*it] == 1)
				sum += *it;
		}
	} while(next_perm(num.begin(), num.end()));
	
	return sum;
}

int main(int argc, char **argv) {
	cout << lexicograph_pandigital_sum(9) << endl;
	return 0;
}