#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

// none of these string methods are used at all


string to_string(int n) {
  string str_n;
  while(n > 0) {
    str_n += (n%10 + '0');
    n/=10;
  }
  reverse(str_n.begin(), str_n.end());
  return str_n;
}

string add_last_10digit(string n1, string n2) {
  string large, small;
  if(n1.size() > n2.size()){
    large = n1;
    small = n2;
  }
  else {
    large = n2;
    small = n1;
  }

  char carry = 0;
  string::reverse_iterator l_it = large.rbegin();
  string::reverse_iterator s_it = small.rbegin();
  int i = 0;
  string res;
  while(l_it != large.rend() && i < 10) {
    char s = *l_it - '0';
    if(s_it != small.rend()) {
      s += (*s_it - '0');
      s_it++;
    }
    s += carry;
    carry = s/10;
    res += (s%10+'0');
    l_it++;
    i++;
  }

  while(carry > 0 && i < 10) {
    res += (carry%10 + '0');
    carry /= 10;
    i++;
  }

  reverse(res.begin(), res.end());

  //  cout << large << " " << small << " " << res << endl;

  return res;
}

string multiply(string n, int m) {
  string res("0");
  for(int i = 0; i < m; i++) {
    res = add_last_10digit(res, n);
  }
  return res;
}

string pow_a_b(int a, int b) {
  if(b == 0) return string("1");

  string res(to_string(a));
  for(int i = 1; i < b; i++) {
    res = multiply(res, a);
  }

  return res;
}

void slow_version(int argc, char **argv) {
  int limit = atoi(argv[1]);
  string last_10digit_sum;
  for(int i = 0; i < limit; i++) {
    last_10digit_sum = add_last_10digit(pow_a_b(i+1, i+1), last_10digit_sum);
  }
  
  cout << last_10digit_sum << endl;
}

typedef long long unsigned int vlong;

vlong modular_pow(vlong a, vlong b, vlong modulus) {
  vlong c = 1;
  for(int i = 0; i < b; i++) {
    c = (c*a)%modulus;
  }
  return c;
}

vlong pow_vlong(vlong base, vlong exp) {
  vlong res = 1;
  for(int i = 0; i < exp; i++) {
    res *= base;
  }

  return res;
}

int main(int argc, char **argv) {
  vlong modulus = pow_vlong(10,atoi(argv[2]));
  int limit = atoi(argv[1]);

  vlong sum = 0;
  for(vlong i = 1; i <= limit; i++) {
    sum += modular_pow(i, i, modulus);
  }

  cout << sum%modulus << endl;
  return 0;
}

