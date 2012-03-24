#include <iostream>
#include <string>
#include <cmath>

using namespace std;

typedef long long int vlong;

vlong to_vlong(string str) {
	vlong n = 0;
	for(string::const_iterator it = str.begin(); it != str.end(); it++)
		n = n*10 + ((*it)-'0');
	return n;
}

vlong reverse(vlong n) {
	vlong rev = 0;
	while(n > 0) {
		rev = rev*10 + n%10;
		n /= 10;
	}
	return rev;
}

template<class T>
void swap2(T &item1, T &item2) {
	T temp = item1; 
	item1 = item2;
	item2 = temp;
}

template<class T>
void reverse(T left, T right) {
	while(left < right-1) {
		swap2(*left, *(right-1));
		left++; right--;
	}
}

string to_string(vlong n) {
	string str;
	while(n > 0) {
		str += (n%10 + '0');
		n /= 10;
	}
	reverse(str.begin(), str.end());
	return str;
}

string next_pandigital(string n) {
	string::iterator pos = n.begin();
	for(string::iterator it = n.begin(); (it+1) != n.end(); it++)
		if(*it > *(it+1))
			pos = it;
			
	string::iterator swap_pos = pos;
	for(string::iterator it = pos+1; it != n.end(); it++)
		if(*it < *pos)
			swap_pos = it;
	
	swap2(*pos, *swap_pos);
	reverse(pos+1, n.end());
	return n;
}

static vlong lowest_n_pandigital = 1234567;
vlong next_pandigital(int n) {
	if(n == lowest_n_pandigital) {
		lowest_n_pandigital /= 10;
		return reverse(lowest_n_pandigital);
	}
	
	return to_vlong(next_pandigital(to_string(n)));
}

bool is_prime(int n) {
	if(n==2 || n==3 || n==5 || n==7) return true;
	if(n<11) return false;
	if(n%2 == 0 || n%3 == 0) return false;
	
	int sqrt_n = ceil(sqrt(n));
	for(int i = 5; i <= sqrt_n; i+=6) {
		if(n%i == 0) return false;
		if(n%(i+2) == 0) return false;
	}
	return true;
}

int main(int argc, char **argv) {
	for(vlong i = 7654321; i > 1; i = next_pandigital(i)) {
		//cout << i << endl;
		if(is_prime(i)) {
			cout << i << endl;
			break;
		}
	}

	return 0;
}
