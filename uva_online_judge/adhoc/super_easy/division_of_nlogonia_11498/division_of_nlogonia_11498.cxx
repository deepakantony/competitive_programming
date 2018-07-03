#include <iostream>
using namespace std;
int main(int argc, char *argv[])
{
  int K;

  while( (cin >> K) && K > 0 ) {
    int DX, DY; cin >> DX >> DY;

    while(K--) {
      int X, Y; cin >> X >> Y;

      if (X==DX || Y==DY) cout << "divisa\n";
      else if(X<DX && Y>DY) cout << "NO\n";
      else if(X>DX && Y>DY) cout << "NE\n";
      else if(X<DX && Y<DY) cout << "SO\n";
      else if(X>DX && Y<DY) cout << "SE\n";
    }
  }
  
  return 0;
}
