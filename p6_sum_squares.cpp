#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;

int main(int argc, char *argv[]) {
	int n = atoi(argv[1]);
	int sum_of_squares = (n+1)*(2*n+1)*n/6;
	int square_of_sum = n*(n+1)/2;
	square_of_sum *= square_of_sum;
	
	cout << square_of_sum - sum_of_squares << endl;
	
	return 0;
}