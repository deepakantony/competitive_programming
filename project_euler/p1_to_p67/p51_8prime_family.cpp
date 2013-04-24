#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <algorithm>

using namespace std;

bool is_prime(int n) {
  if(n==2 && n == 3 && n == 5 && n == 7) 
    return true;
  if(n%2 == 0 || n%3 == 0) return false;
  int sqrt_n = ceil(sqrt(n));
  for(int i = 5; i <= sqrt_n; i+=6) {
    if(n%i == 0) return false;
    if(n%(i+2) == 0) return false;
  }
  return true;
}

int to_int(string str_n) {
  int n = 0;
  for(string::const_iterator it = str_n.begin(); it != str_n.end(); it++)
    n = n*10+(*it - '0');

  return n;
}

string to_string(int n) {
  string str_n;
  while(n>0) {
    str_n += (n%10 + '0');
    n /= 10;
  }
  reverse(str_n.begin(), str_n.end());

  return str_n;
}

// replace all a's with b
void replace_all(string &str_n, char a, char b) {
  for(string::iterator start = str_n.begin(); start != str_n.end(); start++) {
    if(*start == a)
      *start = b;
  }
}

bool is_k_prime(string str_n, int k) {
  //cout << str_n << " ";
  char i = 0;
  if(str_n[0] == '*') i++;
  int n_primes = 0;
  for(; i < 10; i++) {
    string new_str_n(str_n);
    replace_all(new_str_n, '*', (char)(i+'0'));
    if(is_prime(to_int(new_str_n))) {
      //cout << to_int(new_str_n) << " ";
      n_primes++;
    }
  }
  //cout << endl;
  if(n_primes >= k) return true;
  else return false;
}
  

bool is_k_prime(int n, int k, string &out_str) {
  if(n < 11) return false;
  if(k < 6) return true;

  string str_n = to_string(n);
  string stars;
  for(int i = 0; i < str_n.size()-1; i++) {
    stars += '*';
    for(int pos = 0; pos+i < str_n.size()-1; pos++) {
      string stard_str_n = string(str_n.begin(), str_n.begin()+pos) + stars
        + string(str_n.begin()+pos+stars.size(), str_n.end());

      if(is_k_prime(stard_str_n, k)) {
        out_str = stard_str_n;
        return true;
      }
    }
  }

  return false;
}

bool is_repeating_digits(int n, int digits, int &digit) {
  int repeating[10];
  for(int i = 0; i < 10; i++)
    repeating[i] = 0;

  n/=10;
  while(n>0) {
    repeating[n%10]++;
    if(repeating[n%10] == digits) {
      digit = n%10;
      return true;
    }
    n/=10;
  }

  return false;
}

int smallest(string str_n) {
  char i = 0;
  if(str_n[0] == '*') i++;
  for(; i < 10; i++) {
    string new_str_n(str_n);
    replace_all(new_str_n, '*', i+'0');
    if(is_prime(to_int(new_str_n)))
      return to_int(new_str_n);
  }
  return 0;
}

int smallest_k_primes_family(int k) {
  for(int i = 100001; i < 1000000; i+=2) {
    int digit;
    if(is_prime(i) && is_repeating_digits(i, 3, digit)) {
      string str_i = to_string(i);
      int j = 0;
      for(string::iterator it = str_i.begin(); it != str_i.end(); it++)
	if(*it == '0'+digit && j < 3) {
	  *it = '*';
	  j++;
	}

      if(j == 3 && is_k_prime(str_i, k)) {
	return smallest(str_i);
      }
    }
  }
  return 0;
}

int main(int argc, char **argv) {
  cout << smallest_k_primes_family(8) << endl;
  return 0;
}

