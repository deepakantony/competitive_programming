#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>

using namespace std;

typedef long long unsigned int vlong;

vlong to_vlong(string str) {
  vlong n = 0;
  for(string::const_iterator it = str.begin(); it != str.end(); it++)
    n = n*10 + (*it - '0');
  return n;
}

template<class T>
void _iter_swap(T begin, T end) {
  typename iterator_traits<T>::value_type temp = *begin;
  *begin = *end;
  *end = temp;
}

template<class T>
void _reverse(T begin, T end) {
  end--;
  while(begin < end)
    _iter_swap(begin++, end--);
}

string to_string(vlong n) {
  string res;
  while(n > 0) {
    res += n%10+'0';
    n /= 10;
  }
  _reverse(res.begin(), res.end());
  return res;
}

template<class T>
void _sort(T begin, T end) {
  if(begin >= end-1) return;

  T pivot = begin + (end-begin)/2;
  _iter_swap(begin,pivot);
  pivot = begin;

  T left_iter = begin+1;
  T right_iter = end-1;
  while(left_iter <= right_iter) {
    if(*left_iter < *pivot)
      pivot++;
    else {
      _iter_swap(left_iter,right_iter);
      right_iter--;
    }
  }

  _iter_swap(right_iter,pivot);
  pivot = right_iter;

  _sort(begin, right_iter);
  _sort(right_iter+1, end);
}

template<class T>
bool next_perm(T begin, T end) {
  T pos = begin;
  for(T it = begin; (it+1) != end; it++)
    if(*it < *(it+1))
      pos = it;

  T swap_pos = pos;
  for(T it = pos+1; it != end; it++)
    if(*it > *pos)
      swap_pos = it;

  if(pos == swap_pos) return false;

  _iter_swap(pos, swap_pos);
  _reverse(pos+1, end);
  return true;
}

template<class T>
void update_beg_zero(T begin, T end) {
  if(*begin == '0') {
    T swap_pos = begin;
    while(*swap_pos == '0' && swap_pos != end)
      swap_pos++;
    if(swap_pos != end)
      _iter_swap(swap_pos, begin);
  }
}


int main(int argc, char **argv) {
  vlong num = atol(argv[1]);
  string s_num = to_string(num);
  cout << "Integer: " << num << endl;
  cout << "String: " << s_num << endl;
  _sort(s_num.begin(), s_num.end());
  cout << "Sorted: " << s_num << endl;
  update_beg_zero(s_num.begin(), s_num.end());
  cout << "Beg zero updated: " << s_num << endl;
  cout << "Permutation begin: [ ";
  do {
    cout << s_num << " ";
  }while(next_perm(s_num.begin(), s_num.end()));
  cout << "]" << endl;

  num = to_vlong(s_num);
  cout << "Final integer: " << num << endl;
  return 0;
}
