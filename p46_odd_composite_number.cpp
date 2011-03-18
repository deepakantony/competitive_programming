#include <iostream>
#include <vector>
#include <climits>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <cstdlib>

using namespace std;

typedef unsigned int vlong;

bool is_prime(vlong n, const vector<vlong> &primes) {
  int sqrt_n = ceil(sqrt(n));
  for(vector<vlong>::const_iterator it = primes.begin(); it != primes.end() && *it <= sqrt_n; it++)
    if(n%(*it)==0) return false;

  return true;
}

vector<vlong> generate_primes(vlong n) {
  vector<vlong> primes;
  primes.push_back(2);
  primes.push_back(3);
  
  for(vlong i = 5; i < n; i+=6) {
    if(is_prime(i,primes)) primes.push_back(i);
    if(is_prime(i+2, primes)) primes.push_back(i+2);
  }

  return primes;
}

int main(int argc, char **argv) {
  vector<vlong> primes = generate_primes(atol(argv[1]));

  

  return 0;
}
