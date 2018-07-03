#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
  cin.unsetf(ios::skipws);
  char inp;
  bool backquote = true;
  while(cin >> inp) {
    if(inp == '"') { 
      if (backquote) cout << "``"; else { cout << "''"; } 
      backquote = !backquote; 
    }
    else cout << inp;
  }

  return 0;
}
