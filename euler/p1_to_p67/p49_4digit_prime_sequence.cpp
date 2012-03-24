#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <vector>
#include <bitset>

using namespace std;

bool is_prime(int n) {
  if(n == 2 || n == 3 || n == 5 || n == 7) return true;
  if(n%2 == 0 || n%3 == 0) return false;

  int sqrt_n = ceil(sqrt(n));
  for(int i = 5; i <= sqrt_n; i+=6) {
    if(n%i == 0) return false;
    if(n%(i+2) == 0) return false;
  }
  return true;
}

vector<int> digit_primes() {
  vector<int> primes;
  for(int i = 1001; i < 10000; i+=2) 
    if(is_prime(i))
      primes.push_back(i);
  return primes;
}

string to_string(int n) {
  string str_n;
  while(n>0){
    str_n += (n%10+'0');
    n /= 10;
  }
  reverse(str_n.begin(), str_n.end());
  return str_n;
}

int to_int(string str_n) {
  int n = 0;
  for(string::const_iterator it = str_n.begin(); it != str_n.end(); it++) {
    n = n*10 + (*it - '0');
  }
  return n;
}

string next_perm(string str_n) {
  string::iterator pos = str_n.begin();
  for(string::iterator it = pos+1; (it+1) != str_n.end(); it++)
    if(*it < *(it+1))
      pos = it;

  string::iterator swap_pos = pos;
  for(string::iterator it = pos + 1; it != str_n.end(); it++)
    if(*pos < *it)
      swap_pos = it;

  if(pos == swap_pos) return string("");

  iter_swap(pos, swap_pos);
  reverse(pos+1, str_n.end());
  return str_n;
}

bool ispermutation(int a, int b) {
  bitset<10> a_1, b_1;

  while(a>0) {
    a_1.set(a%10);
    a /= 10;
  }
  while(b>0) {
    b_1.set(b%10);
    b /= 10;
  }

  for(int i = 0; i < 10; i++)
    if(a_1[i] != b_1[i]) return false;

  return true;
}

int main(int argc, char **argv) {
  int limit = 10000 - 2*3330;
  for(int i = 1001; i < limit; i+=2) {
    if(is_prime(i) && is_prime(i+3330) && is_prime(i+2*3330) && 
       ispermutation(i, i+3330) && ispermutation(i,i+2*3330))
      cout << i << " " << i+3330 << " " << i + 2*3330 << endl;
  }
  
  return 0;
}
