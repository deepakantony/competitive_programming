#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>

using namespace std;

int int_pow(int a, int b) {
	int pow_a_b = 1;
	for(int i = 0; i < b; i++)
		pow_a_b *= a;
		
	return pow_a_b;
}

int count_distinct_terms(int max) {
	bool distinct[max+1][max+1];
	
	for(int i = 0; i <= max; i++)
		for(int j = 0; j <= max; j++)
			distinct[i][j] = true;
	
	for(int i = 2; i*i <= max; i++)
		for(int j = 2; int_pow(i,j) <= max; j++) {
			int pow_i_j = int_pow(i,j);
			
			for(int k = 1; k < j; k++)
				for(int b = 2; (b*j/k) <= max; b++)
					if((j*b)%k == 0)
						distinct[pow_i_j][b] = false;
		}
	
	int count = 0;
	
	for(int i = 2; i <= max; i++)
		for(int j = 2; j <= max; j++)
			if(distinct[i][j]) count++;
	
	return count;
}

int main(int argc, char **argv) {
	cout << count_distinct_terms(atoi(argv[1])) << endl;

	return 0;
}
