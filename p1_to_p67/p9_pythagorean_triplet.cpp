#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;

int main(int argc, char *argv[]) {
	int a, b, c;
	int sum = atoi(argv[1]);
	
	// we shall use eclids formula for finding triplets
	// keeping m > n the triplet would be (m2-n2, 2mn, m2+n2)
	int n = 1;
	int m = 2;
	a = m*m - n*n;
	b = 2*m*n;
	c = m*m + n*n;
	while((a+b+c) < sum) {			
		if((a+b+c) > sum) {
			n++;
			m = n+1;
		}
		else m++;
		
		a = m*m - n*n;
		b = 2*m*n;
		c = m*m + n*n;
		
		for(int k = 2; k*(a+b+c) <= sum; k++) {
			if(k*(a+b+c) == sum) {
				a *= k;
				b *= k;
				c *= k;
			}
		}
	}
	
	if((a+b+c) == sum) {
		cout << a*b*c << endl;
		cout << a << " " << b << " " << c << endl;
		cout << a*a << " " << b*b << " " << c*c << endl;
	}
	else
		cout << "Could not find a+b+c = " << sum << endl;
	
	return 0;
}
