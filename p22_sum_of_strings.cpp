#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

int string_number(string str) {
	string::const_iterator it = str.begin();
	int sum = 0;
	while(it != str.end()) {
		if(isalpha(*it))
			sum = sum + (tolower(*it) - 'a' + 1);
		++it;
	}
	
	return sum;
}


typedef vector<string>::const_iterator T;
long long unsigned int sum_of_string_number(T left, T right) {
	long long unsigned int sum = 0;
	
	int idx = 1;
	for(T it = left; it != right; it++, idx++) {
		sum += (idx * string_number(*it));
		cout << idx << " " << *it << " " << string_number(*it) << endl;
	}
	
	return sum;
}

vector<string> construct_vector(ifstream &in) {
	char c;
	vector<string> res;	
	string cur_string;
	bool start_string = false;
	while(in.good()){
		c = in.get();
		if(c == '"')
			if(!start_string)
				start_string = true;
			else {
				res.push_back(cur_string);
				cur_string = "";
				start_string = false;
			}
		else if(isalpha(c) && start_string) {
			cur_string += c;
		}
	}
	return res;
}

int main(int argc, char **argv) {
	ifstream in(argv[1]);
	
	vector<string> vec = construct_vector(in);
	sort(vec.begin(), vec.end());
	cout << sum_of_string_number(vec.begin(), vec.end()) << endl;
	
	in.close();
	
	return 0;
}
	
