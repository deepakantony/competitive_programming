#include <iostream>

using namespace std;

int sum_digits(int n) {
  int sum = 0;
  while(n>0) { sum += n%10; n/=10; }
  return sum;
}

int main(int argc, char *argv[])
{
  int N; 
  while( (cin >> N) && N > 0 ) {
    while( N > 9 ) N = sum_digits(N);
    cout << N << "\n";
  }

  return 0;
}
