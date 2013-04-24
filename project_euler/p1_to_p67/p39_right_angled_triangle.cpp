#include <iostream>
#include <cstdlib>

using namespace std;

int num_of_sols(int p) {
	int a_max = p/2;
	int sols = 0;
	
	for(int a = 1; a < a_max; a++) {
		int b = (p*(p-2*a))/(2*(p-a));
		if(b < a) break;
		if((p*(p-2*a))%(2*(p-a)) == 0) sols++;
	}
	return sols;
}

int main(int argc, char **argv) {
	// solve a^2 + b^2 = (p-a-b)^2
	// b = (p*(p-2*a))/(2*(p-a))
	
	int largest = 0;
	int p = 0;
	for(int i = 2; i <= 1000; i += 2) {
		int sols = num_of_sols(i);
		if(sols > largest) {
			largest = sols;
			p = i;
		}
	}
	cout << p << " " << largest << endl;

	return 0;
}
