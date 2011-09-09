#include <iostream>
#include <cstdlib>
#include <bitset>

using namespace std;

int reverse(int n) {
	int rev = 0;
	while(n > 0) {
		rev = rev*10+n%10;
		n /= 10;
	}
	return rev;
}

int get_pandigital(int num, int n) {
	int pandigital = 0;
	for(int i = 1; i <= n; i++) {
		int prod = reverse(num*i);
		do {
			pandigital = pandigital*10 + (prod%10);
		}while((prod=prod/10)>0);
	}
	return pandigital;
}

void display_pandigital(int num, int n, int pandigital) {	
	for(int i = 1; i <= n; i++) 
		cout << num << " x " << i <<"\t" << ": " << num*i << endl;
	cout << "Pandigital: " << pandigital << endl;
}

int pandigital_product(int n) {
	bitset<9> digit_cov;
	
	int tot_digits = 0;
	int i = 1;
	while(tot_digits < 9) {
		int prod = i * n;
		
		while(prod > 0) {
			int dig = prod%10;
			if(dig == 0) return 0;
			if(digit_cov[dig-1]) return 0;
			else {
				digit_cov.set(dig-1);
			}
			tot_digits++;
			
			prod = prod/10;
		}
		
		i++;
	}
	
	return i-1;
}

int main(int argc, char **argv) {
	int largest_p = 0;
	int largest_n = 0;
	int largest_num = 0;
	for(int i = 1; i <= 9999; i++) {
		int n = pandigital_product(i);
		int p = get_pandigital(i,n);
		if(n>0 && largest_p < p) {
			largest_p = p;
			largest_n = n;
			largest_num = i;
		}
	}
	
	display_pandigital(largest_num, largest_n, largest_p);

	return 0;
}
