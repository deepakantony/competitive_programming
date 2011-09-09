#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <map>

using namespace std;

bool is_prime(int n, const vector<int> primes) {
  int sqrt_n = ceil(sqrt(n));
  for(vector<int>::const_iterator it = primes.begin(); it != primes.end() && *it <= sqrt_n; it++)
    if(n%(*it) == 0) return false;

  return true;
}

void all_primes(int limit, vector<int> &primes) {
  primes.clear();
  primes.push_back(2);
  primes.push_back(3);
  for(int i = 5; i < limit; i+=6) {
    if(is_prime(i, primes)) primes.push_back(i);
    if(is_prime(i+2, primes)) primes.push_back(i+2);
  }
}

template<class T>
int summation(T start, T end) {
  int sum = 0;
  for(T it = start; it != end; it++)
    sum += *it;
  return sum;
}

int main(int argc, char **argv) {
  int p=2, n_primes=1;

  int limit = atoi(argv[1]);

  vector<int> primes;
  all_primes(limit, primes);

  vector<int>::const_iterator low_p, high_p;
  low_p = high_p = primes.begin();
  int sum = 0;

  while(primes.end() - low_p >= n_primes) {
    while((sum+(*high_p)) <= *(primes.end()-1)) {
      sum += *high_p;
      if(is_prime(sum, primes) && sum > p && n_primes < high_p-low_p+1) {
	n_primes = high_p - low_p + 1;
	p = sum;
      }
      high_p++;
    }
    
    low_p++;
    high_p = low_p + n_primes;
    sum = summation(low_p, high_p);
  }

  cout << p << " " << n_primes << endl;

  return 0;
}

