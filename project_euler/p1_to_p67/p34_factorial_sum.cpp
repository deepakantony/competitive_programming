#include <iostream>

using namespace std;

typedef long long unsigned int vlong;

vlong factorial(vlong f) {
	vlong fact = 1;
	for(vlong i = 2; i <= f; i++)
		fact *= i;
	return fact;
}

vlong sum_of_digits_factorial(vlong n) {
	static const vlong fact[] = {1,1,2,factorial(3),factorial(4),factorial(5),
						factorial(6),factorial(7),factorial(8),factorial(9)};
	vlong sum = 0;
	
	while(n >= 1){
		sum += fact[n%10];	
		n = n/10;
	}
	
	return sum;
}

int main(int argc, char **argv) {
	vlong sum = 0;
	
	vlong low = 10;
	vlong high = low*10-1;
	while(low < sum_of_digits_factorial(high)) {
		vlong sum_of_high_digits = sum_of_digits_factorial(high);
		for(int i = low; i < high && i <= sum_of_high_digits; i++) {
			if(i == sum_of_digits_factorial(i)) {
				sum += i;
				cout << i << endl;
				}
		}
		low *= 10;
		high = low*10-1;
	}
	
	cout << sum << endl;

	return 0;
}
