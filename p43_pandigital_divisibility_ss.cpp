#include <iostream>
#include <string>
#include <algorithm>
#include <bitset>
#include <queue>

using namespace std;
typedef string::iterator str_it;

bool lexicograph_perm(string &num) {
	str_it pos = num.begin();
	for(str_it it = num.begin(); (it+1) != num.end(); it++)
		if(*it < *(it+1))
			pos = it;
		
	str_it swap_pos = pos;
	for(str_it it = pos+1; it != num.end(); it++)
		if(*it > *pos)
			swap_pos = it;

	if(pos == swap_pos)
		return false;
	
	iter_swap(pos, swap_pos);
	reverse(pos+1, num.end());
	return true;
}

template<class T>
bool check_divisibility(T *start, T n) {
	return ((*start*100 + *(start+1)*10 + *(start+2))%n == 0);
}

typedef long long int vlong;
vlong is_prime_divisibility(string pan) {
	int d[10];
	
	int i = 0;
	for(str_it it = pan.begin(); it != pan.end(); it++)
		d[i++] = *it-'0';
	int primes[] = {2,3,5,7,11,13,17};
	for(int i = 0; i < 7; i++)
		if(!check_divisibility(d+i+1,primes[i]))
			return 0;
	
	vlong n = 0;
	for(int i = 0; i < 10; i++)
		n = n*10+d[i];
	
	return n;
}

void slow_version() {

	vlong sum = 0;
	string p("0123456789");
	do {
		sum += is_prime_divisibility(p);
	}while(lexicograph_perm(p));
	
	cout << sum << endl;
}

bool is_distinct_digits(string n) {
	bitset<10> distinct;
	for(str_it it = n.begin(); it!= n.end(); it++) {
		if(distinct[*it-'0']) return false;
		distinct.set(*it-'0');
	}
	return true;
}

vlong to_vlong(string n) {
	vlong num = 0;
	for(str_it it = n.begin(); it!= n.end(); it++)
		num = num*10 + (*it - '0');
	return num;
}

string to_string(vlong n) {
	string str_n;
	while(n > 0){
		str_n += ((char)(n%10)+'0');
		n/=10;
	}
	return str_n;
}

void fast_version() {
	int n_primes = 7;
	int primes[] = {2,3,5,7,11,13,17};

	queue<string> old_Q; // breadth first search
	queue<string> new_Q;
	
	// initialize the queue
	for(int i = 0; i < 10; i++) // for d0
		for(int j = 1; j*2 < 1000; j++){ 
			string n;
			if(i == 0) n = "0";
			n += to_string(i*1000+j*2);
			if(is_distinct_digits(n)) {
				old_Q.push(n);
			}
		}
	
	for(int i = 1; i < n_primes; i++) {
		while(!old_Q.empty()){
			string str_n = old_Q.front();
			vlong n = to_vlong(str_n);
			for(int j = 0; j < 10; j++) {
				int ss = (n%100)*10+j;
				string str_new_n = str_n;
				str_new_n += (j+'0');
				if(ss%primes[i] == 0 && is_distinct_digits(str_new_n))
					new_Q.push(str_new_n);
			}
			
			old_Q.pop();
		}
		while(!new_Q.empty()) {
			old_Q.push(new_Q.front());
			new_Q.pop();
		}
	}
	
	vlong sum = 0;
	while(!old_Q.empty()){
		cout << old_Q.front() << endl;
		sum += to_vlong(old_Q.front());
		old_Q.pop();
	}
	
	cout << sum << endl;
}

int main(int argc, char **argv) {
	fast_version();
	return 0;
}
