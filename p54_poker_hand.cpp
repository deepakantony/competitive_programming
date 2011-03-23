#include <iostream>
#include <fstream>

using namespace std;

enum suite { S, H, D, C};
enum hand {J=11, Q, K, A};

struct Card {
  Card(string c) {
    
  }

  bool is_pair(const Card &c) const;
  bool is_same_suite(const Card &c) const;
  bool is_identical(const Card &c) const;

  int suite, hand;
}

struct PokerHand {
  PokerHand(string card1, string card2, string card3, 
	    string card4, string card5) {
  }

}  

int main(int argc, char **argv) {

  int count = 0;

  ifstream in(argv[1]);

  PokerHand player1, player2;
  while(in.good()) {
    if(in >> player1 && in >> player2) {
      if(player1 > player2)
	count++;
    }
    else break;
  }
  in.close();

  cout << count << endl;

  return 0;
}
