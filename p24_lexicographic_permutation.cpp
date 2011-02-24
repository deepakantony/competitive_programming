#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

//template<class T>
typedef string::iterator T;
bool next_permutation(T start, T end) {
	// find pos such that *pos < *(pos+1)
	T pos = start;
	for(T it = start; (it+1) != end; it++)
		if(*it < *(it+1))
			pos = it;
		
	if(*pos > *(pos+1)) return false;
	
	// find the swap_pos
	T swap_pos = pos+1;
	for(T it = pos+2; it != end; it++)
		if(*it > *pos)
			swap_pos = it;
			
	iter_swap(pos, swap_pos);
	
	reverse(pos+1, end);
	
	return true;
}

int main(int argc, char **argv) {
	string lex_str(argv[1]); // input should be "0123456789"
	for(int i = 0; i < 999999; i++) // The first permutation was already input
		next_permutation(lex_str.begin(), lex_str.end());
	cout << lex_str << endl;
	return 0;
}
