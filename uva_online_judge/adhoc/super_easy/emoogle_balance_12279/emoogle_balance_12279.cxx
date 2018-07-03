#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
  int N, i = 1, k;
  while((cin >> N) && N > 0) {
    int balance = 0;
    while(N--) {
      cin >> k;
      if (k == 0) --balance;
      else ++balance;
    }

    cout << "Case " << i << ": " << balance << "\n";
    ++i;
  }
  return 0;
}
