#include <iostream>

using namespace std;

int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};

struct Fraction;
Fraction reduce(Fraction f);

struct Fraction {
	int numer;
	int denom;
	
	Fraction(): numer(0), denom(0) {};
	Fraction(int n, int d) : numer(n), denom(d) {};
	
	bool operator==(const Fraction &f) {
		Fraction reduced_f = reduce(f);
		Fraction reduced_this = reduce(*this);
		return (reduced_f.numer == reduced_this.numer &&
				reduced_f.denom == reduced_this.denom);
	}
	
	Fraction operator*(const Fraction &f) {
		return Fraction(this->numer*f.numer, this->denom*f.denom);
	}
	
	Fraction operator=(const Fraction &f) {
		this->numer = f.numer;
		this->denom = f.denom;
		return *this;
	}
};

Fraction reduce(Fraction f) {
	for(int i = 0; primes[i] != 97 && f.numer >= primes[i]; i++) {
		while(f.numer%primes[i] == 0 && f.denom%primes[i] == 0) {
			f.numer /= primes[i];
			f.denom /= primes[i];
		}
	}
	
	return f;
}

bool is_curious(Fraction f) {
	int numer1 = f.numer/10;
	int numer2 = f.numer%10;
	int denom1 = f.denom/10;
	int denom2 = f.denom%10;
	
	if((numer1 == denom1 && f == Fraction(numer2,denom2)) || 
		(numer2 == denom1 && f == Fraction(numer1,denom2)) || 
		(numer1 == denom2 && f == Fraction(numer2,denom1)) || 
		(numer2 == denom2 && f == Fraction(numer1,denom1)))
		return true;
		
	return false;
}

int main(int argc, char **argv) {
	Fraction f(1,1);
	for(int i = 10; i < 100; i++)
		for(int j = i+1;j < 100; j++)
			if(i%10 && j%10) {
				if(is_curious(Fraction(i,j))) {
					cout << i << "/" << j << endl;
					f = f * Fraction(i,j);
				}
			}

	cout << f.numer << "/" << f.denom << endl;
	f = reduce(f);
	cout << f.numer << "/" << f.denom << endl;

	return 0;
}
