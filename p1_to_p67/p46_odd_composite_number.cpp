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

bool is_square(vlong n) {
  double sqrt_n = sqrt(n);
  return ceil(sqrt_n) == floor(sqrt_n);
}

bool is_goldbach_comp(vlong n, vector<vlong> &primes) {
  for(vector<vlong>::const_iterator it = primes.begin(); *it < n; it++) {
    vlong n_it = n - *it;
    if(n_it%2) continue;
    if(is_square(n_it/2)) return true;
  }
  return false;
}


int main(int argc, char **argv) {
  vlong max_size = atol(argv[1]);
  vector<vlong> primes = generate_primes(max_size);

  for(vlong  i = 9; i < max_size; i+=2) {
    if(!is_prime(i, primes) && !is_goldbach_comp(i, primes)) {
      cout << i << endl;
      break;
    }
  }
      

  return 0;
}
