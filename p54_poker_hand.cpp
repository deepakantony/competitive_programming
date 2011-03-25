#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

enum suite { S, H, D, C, Z};
enum rank {
  high_card,
  one_pair,
  two_pairs,
  three_of_a_kind,
  straight,
  flush,
  full_house,
  four_of_a_kind,
  straight_flush
};

struct Card {
  Card() { _suite = Z; _hand = -1; }
  Card(string c) {
    
  }

  bool is_pair(const Card &c) const { return(_hand == c._hand); }
  bool is_same_suite(const Card &c) const { return(_suite == c._suite); }
  bool is_identical(const Card &c) const { 
    return (is_pair(c) && is_same_suite(c)); 
  }

  static bool compare(const Card &c1, const Card &c2) {
    return c1._hand > c2._hand;
  }

  static bool is_straight(Card *c, int n) {
    for(int i = 0; i+1 < n; i++)
      if(c[i]._hand != c[i+1]._hand+1) {
	if(i == n-2 && c[i]._hand == 5 && c[i+1]._hand == 13)
	  return true;
	else return false;
      }
    return true;
  }

  static bool is_flush(Card *c, int n) {
    enum suite s = c[0]._suite;
    for(int i = 1; i < n; i++)
      if(c[i]._suite != s) return false;
    return true;
  }

  enum suite _suite;
  int _hand;
};

struct PokerHand {
  PokerHand(string card1, string card2, string card3, 
	    string card4, string card5) {
    c[1] = Card(card1);
    c[2] = Card(card2);
    c[3] = Card(card3);
    c[4] = Card(card4);
    c[5] = Card(card5);
  }

  int compare(const PokerHand &p) const {
    vector<int> order_of_cards1, order_of_cards2;

    enum rank draw1 = get_draw(*this);
    enum rank draw2 = get_draw(p);

    if(draw1 > draw2) return 1;
    else if(draw2 > draw1) return -1;
    else {
      get_order_of_cards(*this, draw1, order_of_cards1);
      get_order_of_cards(p, draw2, order_of_cards2);

      vector<int>::const_iterator it1 = order_of_cards1.begin();
      vector<int>::const_iterator it2 = order_of_cards2.begin();
      while(it1 != order_of_cards1.end()) {
	if(*it1 > *it2) return 1;
	if(*it2 > *it1) return -1;
	it1++;
	it2++;
      }

      return 0;
    }
  }
  static enum rank get_draw(const PokerHand &p) {
    Card copy_c[5];
    for(int i = 0; i < 5; i++)
      copy_c[i] = p.c[i];
    
    sort(copy_c, copy_c+5, Card::compare);

    // check if its straight flush
    bool straight = Card::is_straight(copy_c,5);
    bool flush = Card::is_flush(copy_c,5);
    
    if(straight && flush) return straight_flush;

    // check for four of a kind
  }
  static void get_order_of_cards(const PokerHand &p, 
				 int draw, vector<int> &order) {
  }
  static bool is_cheating(const PokerHand &p1, const PokerHand &p2) {
    for(int i = 0; i < 5; i++)
      for(int j = 0; j < 5; j++)
	if(p1.c[i].is_identical(p2.c[j]))
	  return true;
    return false;
  }
  bool operator==(const PokerHand &p) const {return this->compare(p)==0;}
  bool operator>(const PokerHand &p) const {return this->compare(p) > 0;}

  Card c[5];
}; 

int main(int argc, char **argv) {

  string h1, h2, h3, h4, h5;
  cin >> h1 >> h2 >> h3 >> h4 >> h5;
  PokerHand p1(h1,h2,h3,h4,h5);
  cin >> h1 >> h2 >> h3 >> h4 >> h5;
  PokerHand p2(h1,h2,h3,h4,h5);
  if(PokerHand::is_cheating(p1,p2))
    cout << "Card cheating" << endl;
  else if (p1 == p2)
    cout << "Split pot" << endl;
  else if (p1 > p2)
    cout << "Player1 wins" << endl;
  else cout << "Player 2 wins" << endl;

  return 0;
  /*
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

  return 0;*/
}
