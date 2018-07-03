#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
  int T; cin >> T;
  int A,B;

  while(T--) {
    cin >> A >> B;
    if ( A > B ) cout << ">\n";
    else if ( A < B ) cout << "<\n";
    else cout << "=\n";
  }

  return 0;
}
