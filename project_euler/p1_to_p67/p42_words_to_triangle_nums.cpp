#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>

using namespace std;

bool is_triangle(int n) {
	n *= 2;
	int sqrt_n = floor(sqrt(n));
	return (n == sqrt_n*(sqrt_n+1));
}

int string_number(string s) {
	int n = 0;
	for(string::const_iterator it = s.begin(); it != s.end(); it++)
		if(isalpha(*it))
			n += (toupper(*it) - 'A' + 1);
			
	return n;
}

int main(int argc, char **argv) {
	ifstream in;
	in.open(argv[1]);
	
	char input[50];
	
	int count = 0;
	while(in.getline(input, 50, ','))
		if(is_triangle(string_number(string(input)))) {
			cout << input << " " << string_number(string(input)) << endl;
			count++;
		}
	
	in.close();
	
	cout << count << endl;

	return 0;
}
