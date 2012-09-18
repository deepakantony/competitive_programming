#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>

using namespace std;

bool is_prime(int n, const vector<int> &primes) {
  int sqrt_n = ceil(sqrt(n));
  for(vector<int>::const_iterator it = primes.begin(); it != primes.end() && *it <= sqrt_n; it++)
    if(n%(*it)==0) return false;

  return true;
}

vector<int> generate_primes(int limit) {
  vector<int> primes;
  primes.push_back(2);
  primes.push_back(3);

  for(int i = 5; i < limit; i+=6){
    if(is_prime(i, primes)) primes.push_back(i);
    if(is_prime(i+2, primes)) primes.push_back(i+2);
  }

  return primes;
}

int number_of_prime_factors(int n, const vector<int> &primes) {
  int num_prime_factors = 0;

  int sqrt_n = ceil(sqrt(n));
  for(vector<int>::const_iterator it = primes.begin(); *it <= sqrt_n && it != primes.end() && n > 1; it++) {
    if(n%(*it)) continue;
    num_prime_factors++;
    while(n%(*it) == 0)
      n /= *it;
  }
  if(n > sqrt_n) num_prime_factors++;

  return num_prime_factors;
}   


int main(int argc, char **argv) {
  int max_limit = atoi(argv[1]);
  vector<int> primes = generate_primes(ceil(sqrt(max_limit)));

  cout << "Primes generated" << endl;

  int n = atoi(argv[2]);

  vector<int> four_cons;

  for(int i = 644; i < max_limit && four_cons.size() < n; i++) {
    int n_prime_factors = number_of_prime_factors(i, primes);
    if(n_prime_factors == n) {
      four_cons.push_back(i);
    }
    else four_cons.clear();
  }

  if(!four_cons.empty())
    cout << four_cons[0] << endl;

  return 0;
}

