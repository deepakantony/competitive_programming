#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

enum suite { S, H, D, C, Z};
enum rank {
  High_card,
  One_pair,
  Two_pairs,
  Three_of_a_kind,
  Straight,
  Flush,
  Full_house,
  Four_of_a_kind,
  Straight_flush
};

ostream& operator<<(ostream &out, const enum rank r) {
  switch(r) {
  case High_card: out << "High card"; break;
  case One_pair: out << "One pair"; break;
  case Two_pairs: out << "Two pairs"; break;
  case Three_of_a_kind: out << "Three of a kind"; break;
  case Straight: out << "Straight"; break;
  case Flush: out << "Flush"; break;
  case Full_house: out << "Full House"; break;
  case Four_of_a_kind: out << "Four of a kind"; break;
  case Straight_flush: out << "Straight flush"; break;
  }
  return out;
}

bool descending(int a, int b) {
  return a > b;
}

struct Card {
  Card() { _suite = Z; _hand = -1; }
  Card(string c) {
    if(isdigit(c[0])) {
      _hand = c[0]-'0';
    }
    else {
      switch(c[0]) {
      case 'T': case 't':
	_hand = 10;
	break;
      case 'J': case 'j':
	_hand = 11;
	break;
      case 'Q': case 'q':
	_hand = 12;
	break;
      case 'K': case 'k':
	_hand = 13;
	break;
      case 'A': case 'a':
	_hand = 14;
	break;
      }
    }

    switch(c[1]) {
    case 'H': case 'h': _suite = H; break;
    case 'S': case 's': _suite = S; break;
    case 'D': case 'd': _suite = D; break;
    case 'C': case 'c': _suite = C; break;
    }
    //cout << "Initialized " << c << " " << _hand << " " << _suite << endl;
  }
  Card(const Card &c) {
    _suite = c._suite;
    _hand = c._hand;
  }

  bool is_pair(const Card &c) const { return(_hand == c._hand); }
  bool is_same_suite(const Card &c) const { return(_suite == c._suite); }
  bool is_identical(const Card &c) const { 
    return (is_pair(c) && is_same_suite(c)); 
  }

  static bool compare(const Card &c1, const Card &c2) {
    return c1._hand > c2._hand;
  }

  static bool is_straight_flush(Card *c, int n, vector<int> &order) {
    return is_straight(c,n,order) && is_flush(c,n,order);
  }

  static bool is_straight(Card *c, int n, vector<int> &order) {
    order.clear();
    for(int i = 0; i < n; i++)
      order.push_back(c[i]._hand);
    sort(order.begin(), order.end(), descending);
    for(int i = 0; i+1 < n; i++)
      if(c[i]._hand != c[i+1]._hand+1) {
	if(i == n-2 && c[i]._hand == 5 && c[i+1]._hand == 13)
	  return true;
	else return false;
      }
    return true;
  }

  static bool is_flush(Card *c, int n, vector<int> &order) {
    order.clear();
    for(int i = 0; i < n; i++)
      order.push_back(c[i]._hand);
    sort(order.begin(), order.end(), descending);

//     for(int i = 0; i < n; i++)
//       cout << c[i]._suite << " ";
//     cout << endl;
    enum suite s = c[0]._suite;
     
    for(int i = 1; i < n; i++)
      if(c[i]._suite != s) return false;
    return true;
  }

  static bool is_four_of_a_kind(Card *c, int n, vector<int> &order) {
    order.clear();
    int h;
    if(c[0].is_pair(c[1]))
      h = c[0]._hand;
    else if(c[0].is_pair(c[2]))
      h = c[0]._hand;
    else h = c[1]._hand;
    order.push_back(h);
    int k = 0;
    for(int i = 0; i < n; i++)
      if(c[i]._hand == h)
	k++;
      else
	order.push_back(c[i]._hand);

    return k == 4;
  }

  static bool is_full_house(Card *c, int n, vector<int> &order) {
    order.clear();
    return (is_two_pair(c, n, order) && is_three_of_a_kind(c,n,order));
  }

  static bool is_three_of_a_kind(Card *c, int n, vector<int> &order) {
    order.clear();
    int p = 0;
    for(int i = 0; i < n-2; i++) {
      for(int j = i+1; j < n; j++)
	if(c[i]._hand == c[j]._hand)
	  p++;

      if(p == 2) {
	order.push_back(c[i]._hand);
	for(int k = 0; k < n; k++)
	  if(c[i]._hand != c[k]._hand)
	    order.push_back(c[k]._hand);
	sort(order.begin()+1, order.end(), descending);
	return true;
      }
      else p = 0;
    }
    return false;
  }

  static bool is_two_pair(Card *c, int n, vector<int> &order) {
    order.clear();
    int p = 0;
    int h1 = -1, h2 = -1;
    for(int i = 0; i+1 < n; i++)
      for(int j = i+1; j < n; j++)
	if(c[i]._hand == c[j]._hand) {
	  order.push_back(c[i]._hand);
	  p++;
	}
    if(p == 2) {
      sort(order.begin(), order.end(), descending);
      for(int i = 0; i < n; i++)
	if(order[0] != c[i]._hand && order[1] != c[i]._hand) {
	  order.push_back(c[i]._hand);
	  break;
	}
      return true;
    }
    return false;
  }

  static bool is_one_pair(Card *c, int n, vector<int> &order) {
    order.clear();
    for(int i = 0; i+1 < n; i++)
      for(int j = i+1; j < n; j++)
	if(c[i]._hand == c[j]._hand) {
	  order.push_back(c[i]._hand);
	  for(int k = 0; k < n; k++)
	    if(c[k]._hand != c[i]._hand)
	      order.push_back(c[k]._hand);
	  sort(order.begin()+1, order.end(), descending);
	  return true;
	}
    return false;
  }
  
  friend ostream& operator<<(ostream &out, const Card &c);

  enum suite _suite;
  int _hand;
};

ostream& operator<<(ostream &out, const Card &c) {
  out << c._suite << "/" << c._hand;
  return out;
}


struct PokerHand {
  PokerHand() {}
  PokerHand(string card1, string card2, string card3, 
	    string card4, string card5) {
    c[0] = Card(card1);
    c[1] = Card(card2);
    c[2] = Card(card3);
    c[3] = Card(card4);
    c[4] = Card(card5);
  }

  int compare(const PokerHand &p) const {
    vector<int> order_of_cards1, order_of_cards2;

    enum rank rank1 = get_rank(*this, order_of_cards1);
    enum rank rank2 = get_rank(p, order_of_cards2);


    if(rank1 > rank2){
      //      cout << rank1 << " " << rank2 << endl;
      return 1;
    }
    else if(rank2 > rank1) return -1;
    else {
      vector<int>::const_iterator it1 = order_of_cards1.begin();
      vector<int>::const_iterator it2 = order_of_cards2.begin();
      while(it1 != order_of_cards1.end()) {
	if(*it1 > *it2) {
	  /*cout << rank1 << " " << rank2 << endl;
	  copy(order_of_cards1.begin(), order_of_cards1.end(),
	       ostream_iterator<int>(cout," ")); cout << endl;
	  copy(order_of_cards2.begin(), order_of_cards2.end(),
	  ostream_iterator<int>(cout," ")); cout << endl;*/
	  return 1;
	}
	if(*it2 > *it1) return -1;
	it1++;
	it2++;
      }

      return 0;
    }
  }
  static enum rank get_rank(const PokerHand &p, vector<int> &order_of_cards) {
    Card copy_c[5];
    for(int i = 0; i < 5; i++)
      copy_c[i] = p.c[i];
    //    for(int i = 0; i < 5; i++)
    //cout << copy_c[i]._suite << " ";
    //cout << endl;
    sort(copy_c, copy_c+5, Card::compare);

    // check if its straight flush
    if(Card::is_straight_flush(copy_c,5,order_of_cards)) return Straight_flush;

    // check for four of a kind
    if(Card::is_four_of_a_kind(copy_c,5,order_of_cards))
      return Four_of_a_kind;

    // full house
    if(Card::is_full_house(copy_c,5,order_of_cards))
      return Full_house;

    // is flush
    if(Card::is_flush(copy_c,5,order_of_cards)) return Flush;

    // is straight
    if(Card::is_straight(copy_c,5,order_of_cards)) return Straight;

    // Three of a kind
    if(Card::is_three_of_a_kind(copy_c, 5,order_of_cards))
      return Three_of_a_kind;

    // Two pair
    if(Card::is_two_pair(copy_c, 5,order_of_cards)) return Two_pairs;

    // One pair
    if(Card::is_one_pair(copy_c, 5,order_of_cards)) return One_pair;

    // high card
    order_of_cards.clear();
    for(int i = 0; i < 5; i++)
      order_of_cards.push_back(p.c[i]._hand);
    sort(order_of_cards.begin(), order_of_cards.end(), descending);
    return High_card;
  }

  static bool is_cheating(const PokerHand &p1, const PokerHand &p2) {
    for(int i = 0; i < 5; i++)
      for(int j = 0; j < 5; j++)
	if(p1.c[i].is_identical(p2.c[j]))
	  return true;
    return false;
  }
  bool operator==(const PokerHand &p) const {return this->compare(p)==0;}
  bool operator>(const PokerHand &p) const {return this->compare(p) == 1;}
  friend istream& operator>>(istream &is, PokerHand &p);
  friend ostream& operator<<(ostream &out, const PokerHand &p);

  Card c[5];
}; 

ostream& operator<<(ostream &out, const PokerHand &p) {
  copy(p.c, p.c+5, ostream_iterator<Card>(out, " "));
  return out;
}


istream& operator>>(istream &is, PokerHand &p) {
  string c1, c2, c3, c4, c5;
  is >> c1 >> c2 >> c3 >> c4 >> c5;
  //cout << c1 << " " << c2 << " " << c3 << " " << c4 << " "<< c5 << " - ";
  p = PokerHand(c1,c2,c3,c4,c5);
  //cout << p << endl;
  return is;
}

int main(int argc, char **argv) {
  /* string h1(argv[1]), h2(argv[2]), h3(argv[3]), h4(argv[4]), h5(argv[5]);
  //  cin >> h1 >> h2 >> h3 >> h4 >> h5;
  PokerHand p1(h1,h2,h3,h4,h5);
  //cin >> h1 >> h2 >> h3 >> h4 >> h5;
  string h6(argv[6]), h7(argv[7]),h8(argv[8]),h9(argv[9]),h10(argv[10]);
  PokerHand p2(h6, h7, h8, h9, h10);
  if(PokerHand::is_cheating(p1,p2))
    cout << "Card cheating" << endl;
  else if (p1 == p2)
    cout << "Split pot" << endl;
  else if (p1 > p2)
    cout << "Player1 wins" << endl;
  else cout << "Player 2 wins" << endl;

  return 0;
  */
  int count = 0;

  ifstream in(argv[1]);

  PokerHand player1, player2;
  while(in.good()) {
    if(in >> player1 && in >> player2) {
      if(player1 > player2) {
	count++;
	//cout << count << endl;
      }
    }
    else break;
  }
  in.close();

  cout << count << endl;

  return 0;
}
