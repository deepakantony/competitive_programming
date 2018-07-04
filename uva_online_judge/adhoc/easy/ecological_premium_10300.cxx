#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
  int T; cin >> T;
  while(T--) {
    int F; cin >> F;
    int burden = 0;
    while(F--) {
      int sz, an, env; cin >> sz >> an >> env;
      burden += (sz*env);
    }
    cout << burden << "\n";
  }

  return 0;
}
