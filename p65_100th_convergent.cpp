#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

template<typename T>
void _swap(T &a, T &b) {
  T temp = a;
  a = b;
  b = temp;
}
  

template<typename IT>
void reverse(IT begin, IT end) {
  while(begin < end)
    _swap(*begin++, *(--end));
}
    

class vlong {
public:
  vlong(const vlong &n) {
    data.clear();
    data = n.data; //(n.data.begin(), n.data.end());
  }
  vlong(int n = 0) {
    data.clear();
    while(n>0) {
      data.push_back(n%10);
      n /= 10;
    }
  }

  vlong& operator+=(const vlong &n) {
    return *this;
  }

  const vlong operator+(const vlong &n) const {
    return vlong(*this) += n;
  }

  vlong& operator*=(const vlong &n) {
    return *this;
  }

  const vlong operator*(const vlong &n) const {
    return vlong(*this) *= n;
  }

  const vlong operator*(const int &n) const {
    return vlong(*this) *= vlong(n);
  }

  string to_string() const {
    string res;
    for(vector<char>::const_iterator it = data.begin(); it != data.end();
	it++)
      res += (*it + '0');

    reverse(res.begin(), res.end());
    return res;
  }
    
private:
  vector<char> data;
};

ostream& operator<<(ostream &out, const vlong &n) {
  out << n.to_string();
  return out;
}

int main(int argc, char **argv) {
  int n = atoi(argv[1]);

  vlong test(n);
  cout << test << endl;
  return 0;

  vlong prev_2 = 1;
  vlong prev_1 = 2;
  for(int i = 1, k = 1; i < n; i++) {
    vlong cur;
    if( (i+1)%3 == 0)
      cur = prev_1*k++ * 2 + prev_2;
    else
      cur = prev_2 + prev_1;
    prev_2 = prev_1;
    prev_1 = cur;
    cout << cur << endl;
  }
  return 0;
}
    
