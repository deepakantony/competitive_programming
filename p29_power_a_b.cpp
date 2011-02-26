#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>

using namespace std;

typedef struct _pair { int x; int y; } power_pair;

int number_of_distinct_terms(int max) {
	vector<power_pair*> power_of_x(max);
	int total_distinct = 0;
	for(int a = 2; a <= max; a++) {
		if(power_of_x[a-2]) {
			vector<bool> distinct_b(max, true);
			int p = power_of_x[a-2]->y;
			for(int i = 1; i < p; i++){
				for(int b = 2; p*b/i <= max; b++) {
					if((b*p)%i == 0){
						distinct_b[p*b/i - 2] = false;
					}
				}
			}
			
			for(int b = 2; b <= max; b++)
				if(distinct_b[b-2])
					total_distinct++;
		}
		else total_distinct += (max-1);

		// Mark all its powers!
		for(int b = 2; b <= max && pow(a,b) <= max; b++)
			if(!power_of_x[pow(a,b) - 2]) {
				int pow_a_b = pow(a,b);
				power_of_x[pow_a_b - 2] = new power_pair;
				power_of_x[pow_a_b - 2]->x = a;
				power_of_x[pow_a_b - 2]->y = b;
			}
	}
	
	return total_distinct;
}

int main(int argc, char **argv) {
	cout << number_of_distinct_terms(atoi(argv[1])) << endl;

	return 0;
}
