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

vector<int> generate_primes(int limit) {
  vector<int> primes;
  primes.push_back(2);
  primes.push_back(3);
  for(int i = 5; i < limit; i+=6) {
    if(is_prime(i)) primes.push_back(i);
    if(is_prime(i+2)) primes.push_back(i+2);
  }
  return primes;
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
  return(is_prime(concat(n1,n2)) && is_prime(concat(n2,n1)));
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
  for(vector<int>::const_iterator it = start; start != end; it++)
    s += *it;
  return s;
}

struct concat_prime {
  int prime;
  int n_concat;
  int sum;
  vector<int> primes;
  concat_prime(int p, int n, int s):prime(p), n_concat(n), sum(s) { primes.push_back(p);}
  concat_prime(int p): prime(p), n_concat(1), sum(p) { primes.push_back(p);}
};

bool is_concat_prime(const concat_prime &prime, const concat_prime &cur_prime) {
  if(prime.n_concat+1 < cur_prime.n_concat) return false;

  if(prime.n_concat+1 == cur_prime.n_concat && prime.sum+cur_prime.prime > cur_prime.sum)
    return false;

  return is_concat_prime(prime.primes, cur_prime.prime);
}

bool update_cur_prime(const concat_prime &prev_prime, concat_prime &cur_prime , int size) {
  if(prev_prime.n_concat + 1 < cur_prime.n_concat) return false;
  // case 1: all of prev_prime concatinable are concatenable with cur_prime
  if(prev_prime.n_concat + 1 != cur_prime.n_concat || prev_prime.sum+cur_prime.prime <= cur_prime.sum)
    if(is_concat_prime(prev_prime.primes, cur_prime.prime)) {
      cur_prime.n_concat = prev_prime.n_concat+1;
      cur_prime.sum = prev_prime.sum + cur_prime.prime;
      cur_prime.primes.clear();
      copy(prev_prime.primes.begin(), prev_prime.primes.end(), back_inserter(cur_prime.primes));
      cur_prime.primes.push_back(cur_prime.prime);
      return true;
    }

  concat_prime temp(cur_prime.prime);
  bool updated = false;
  for(vector<int>::const_iterator it = prev_prime.primes.begin(); 
      it != prev_prime.primes.end(); it++) {
    remove_copy(prev_prime.primes.begin(), prev_prime.primes.end(), back_inserter(temp.primes), *it);
    temp.prime = prev_prime.prime;
    temp.n_concat = prev_prime.n_concat-1;
    temp.sum = prev_prime.sum - *it;
    updated = updated || update_cur_prime(temp, cur_prime, size);
  }
  return updated;
}

concat_prime lowest_concatenable_prime(int size) {
  concat_prime res(3,1,3); // the first prime
  int last_deleted = 0;
  vector<concat_prime> primes;
  primes.push_back(res);

  for(int i = 5; res.n_concat < size || size*i < res.sum && i < 9999; i+=2) {
    if(!is_prime(i)) continue;
    concat_prime cur_prime(i);
    for(vector<concat_prime>::const_iterator it = primes.begin(); it != primes.end(); it++) {
      if(update_cur_prime(*it, cur_prime, size)){
	if(res.n_concat < cur_prime.n_concat || (res.n_concat == cur_prime.n_concat 
						 && res.sum > cur_prime.sum))
	  res = cur_prime;
      }
    }
  /*
    if(res.n_concat > 2 && last_deleted < res.n_concat-2) {
      vector<concat_prime> temp;
      for(vector<concat_prime>::const_iterator it = primes.begin(); it != primes.end(); it++){
	if(it->n_concat >= res.n_concat-1)
	  temp.push_back(*it);
      }
      primes.clear();
      copy(temp.begin(), temp.end(), back_inserter(primes));
      last_deleted = res.n_concat-2;
    }
    if(cur_prime.n_concat >= res.n_concat-1)*/
    
    primes.push_back(cur_prime);
  }

  return res;
}

int main(int argc, char **argv) {
  int size = atoi(argv[1]);

  concat_prime p = lowest_concatenable_prime(size);
  cout << p.prime << " " << p.n_concat << "  " << p.sum << " ( ";
  copy(p.primes.begin(), p.primes.end(), ostream_iterator<int>(cout, " "));
  cout << ") " << endl;
  return 0;
}
