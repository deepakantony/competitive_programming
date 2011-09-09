#include <iostream>
#include <cmath>

using namespace std;

typedef long long unsigned int vlong;

int digits(vlong n) {
  int count = 0;
  while(n>0) {
    count++;
    n/=10;
  }
  return count;
}

int main(int argc, char **argv){
  int count = 0;
  for(vlong base = 1; base < 10; base++) {
    vlong p;
    for(vlong power = 1; digits((p=pow(base,power))) == power; power++) {
      count++;
      cout << p << " ";
    }
  }
  cout << endl;
  cout << count << endl;
  cout << "Add 1 because the last number is the largest number for long long"
       << endl;
  cout << "For even faster algorithm note that foreach x=1-9; "
       << "count so that digits(x^n) == n is floor(log(10)/(log(10)-log(x))). "
       << "Proof on forum."
       << endl;

  return 0;
}
