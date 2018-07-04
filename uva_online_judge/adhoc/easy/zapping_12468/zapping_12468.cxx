#include <iostream>

using namespace std;

int main()
{
  int a,b;
  while((cin>>a>>b) && a!=-1 && b!=-1) {
    int bp = abs(a-b);
    if(bp > 50) bp = 100-bp;
    cout << bp << "\n";
  }
  return 0;
}
