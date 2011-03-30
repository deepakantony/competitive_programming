#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

typedef long long unsigned int vlong;

string to_string(

struct 

struct Fraction {
  Fraction(vlong n, vlong d) : _n(n), _d(d) {};
  Fraction(): _n(0), _d(1) {};

  Fraction operator+(const Fraction &f) const {
    Fraction res(_n, _d);
    if(_d == f._d)
      res._n += f._n;
    else {
      res._n = _n*f._d + f._n*_d;
      res._d *= f._d;
    }
    return res;
  }
  void reciprocal() { vlong temp = _n; _n = _d; _d = temp; }
  friend ostream& operator<<(ostream &, const Fraction &f);
  vlong _n, _d;
};

ostream& operator<<(ostream &out, const Fraction &f) {
  out << f._n << "/" << f._d;
  return out;
}

Fraction square_root_of_2(vlong limit) {
  Fraction f(0, 1);
  Fraction f2(2, 1);
  for(int i = 0; i < limit; i++) {
    f = f + f2;
    f.reciprocal();
  }

  return f+Fraction(1,1);
}

int main(int argc, char **argv) {
  int limit = atoi(argv[1]);
  
  for(int i = 0; i < limit; i++) {
    Fraction f = square_root_of_2(i+1);
    cout << (float)f._n/(float)f._d << endl;
  }
  return 0;
}
