#include <iostream>
#include <cstdlib>

using namespace std;

int sum_spiral_diagonal(int size) {
	if(size%2 == 0) return 0;
	int total_size = size*size;
	int step_size = 2;
	int sum = 1;
	int skipped = 1;
	for(int i = 2; i < total_size; i += step_size) {
		sum += (i+1);
		skipped++;
		if(skipped > 4) {
			skipped = 1;
			step_size += 2;
		}
	}
	return sum;
}

int main(int argc, char **argv) {
	cout << sum_spiral_diagonal(atoi(argv[1])) << endl;
	return 0;
}
