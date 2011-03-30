#include <iostream>
#include <cstdlib>

using namespace std;

typedef long long unsigned int vlong;

struct Fraction {
  Fraction(vlong n, vlong d) : _n(n), _d(d) {};
  Fraction(): _n(0), _d(1) {};

  Fraction operator+(const Fraction &f) const {
    Fraction res(_d, _n);
    if(_d == f._d)
      res._d += f._d;
    else {
      res._d = _n*f._d + f._n*_d;
      res._n *= f._n;
    }
    return res;
  }
  void reciprocal() { vlong temp = _n; _n = _d; _d = temp; }

  vlong _n, _d;
};

Fraction square_root_of_2(vlong limit) {
  Fraction f(1, 1);
  
  for(int i = 0; i < limit; i++) {
    
