#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
  int start, f, s, t;

  while(cin >> start >> f >> s >> t) {
    if(start == 0 && f == 0 && s == 0 && t == 0)
      break;
    int num_turns = 0;

    // step 1
    num_turns += 40*2;
    if (f <= start ) num_turns += (start-f);
    else num_turns += (start+40-f);

    // step 2
    num_turns += 40;
    if (s >= f) num_turns += (s-f);
    else num_turns += (s+40-f);

    // step 3
    if (t <= s) num_turns += (s-t);
    else num_turns += (s+40-t);

    cout << 360*num_turns/40 << "\n";
  }

  return 0;
}
