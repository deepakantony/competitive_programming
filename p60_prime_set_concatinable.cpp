#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
#include <iterator>

using namespace std;

bool is_prime(int n) {
  if(n==2 || n==3 || n==5 || n==7) return true;
  if(n<11 || n%2 == 0 || n%3 == 0) return false;

  int sqrt_n = ceil(sqrt(n));
  for(int i = 5; i <= sqrt_n; i+=6) {
    if(n%i==0) return false;
    if(n%(i+2)==0) return false;
  }
  return true;
}

void generate_primes(int limit, vector<int> &primes) {
  if(limit <= 1) return;
  primes.push_back(2);
  if(limit <= 2) return;
  primes.push_back(3);
  for(int i = 5; i < limit; i+=6) {
    if(is_prime(i)) primes.push_back(i);
    if(is_prime(i+2)) primes.push_back(i+2);
  }
  return;
}

int reverse(int n) {
  int rev = 0;
  while(n>0) {
    rev = rev*10+n%10;
    n/=10;
  }
  return rev;
}

int concat(int n1, int n2) {
  int res = n1;
  n2 = reverse(n2);
  while(n2 > 0) {
    res = res*10+n2%10;
    n2 /= 10;
  }
  return res;
}

bool is_concat_prime(int n1, int n2) {
  return(n1 != n2 && is_prime(concat(n1,n2)) && is_prime(concat(n2,n1)));
}

bool is_concat_prime(vector<int> vec) {
  int size = vec.size();
  for(int i = 0; i < size; i++)
    for(int j = i+1; j < size; j++)
      if(!is_concat_prime(vec[i], vec[j])) return false;
  return true;
}

bool is_concat_prime(const vector<int> &vec, int new_prime) {
  for(vector<int>::const_iterator it = vec.begin(); it != vec.end(); it++) 
    if(!is_concat_prime(*it, new_prime)) return false;
  return true;
}

int sum(vector<int>::const_iterator start, vector<int>::const_iterator end) {
  int s = 0;
  for(vector<int>::const_iterator it = start; it != end; it++)
    s += *it;
  return s;
}

template<class item_type>
ostream& operator<<(ostream& out, const vector<item_type> &vec){
  out << "(" << flush;
  copy(vec.begin(), vec.end(), ostream_iterator<item_type>(out, ","));
  out << ")" << flush;
  return out;
}

bool find_concatenable_primes(const vector<int> &primes, int size, vector<int> &concat_primes) {
  if(size == 0) return true;
  for(vector<int>::const_iterator it = primes.begin(); it != primes.end(); it++) {
    if(is_concat_prime(concat_primes, *it)) {
      concat_primes.push_back(*it);
      if(find_concatenable_primes(primes, size-1, concat_primes))
	return true;
      else
	concat_primes.pop_back();
    }
  }
  return false;
}

int main(int argc, char **argv) {
  if(argc != 3) {
    cout << "Usage: <program> <number of primes> <largest prime/limit>" << endl;
    return -1;
  }
  int size = atoi(argv[1]);
  int limit = atoi(argv[2]);
  
  vector<int> primes;
  generate_primes(limit, primes);

  vector<int> concatenable_primes;
  find_concatenable_primes(primes, size, concatenable_primes);

  cout << "Primes are : ( " << flush;
  copy(concatenable_primes.begin(), concatenable_primes.end(), ostream_iterator<int>(cout," "));
  cout << ")" << endl;
  cout << "Sum : " << sum(concatenable_primes.begin(), concatenable_primes.end()) << endl;

  return 0;
}
