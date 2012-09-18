#include <iostream>
#include <cmath>

using namespace std;

typedef long long unsigned int vlong;

vlong reverse(vlong n) {
  vlong rev = 0;
  while(n>0) {
    rev = rev*10+n%10;
    n /= 10;
  }
  return rev;
}

bool is_palindrome(vlong n) {
  return (n==reverse(n));
}

bool is_lychrel(vlong n) {
  for(int i = 0; i < 50; i++) {
    vlong rev_n = reverse(n);
    n += rev_n;
    if(is_palindrome(n))
      return false;
  }
  return true;
}

int main(int argc, char **argv) {
  int limit = atoi(argv[1]);
  int count = 0;
  for(int i = 0; i < limit; i++) {
    if(is_lychrel(i+1)) {
      count++;
      cout << i+1 << " ";
    }
  }
  cout << endl;
  cout << count << endl;
  return 0;
}
