// TCCC '03 Semifinals 3 Division I Level One
// http://community.topcoder.com/tc?module=ProblemDetail&rd=4493&pm=1259

// 
// First let define the recurrence
// Pos[i] = maximum length of a subsequence with ith entry giving a positive
//        diff
// Neg[i] = maximum length of a subsequence with ith entry giving a negative
//        diff

#include <vector>
#include <cassert>
#include <iterator>
#include <algorithm>
#include <iostream>

using namespace std;

void printvec(vector<int> v) {
	for(auto entry : v)
		cout << entry << " ";
	cout << endl;
}

int longestZigZag(vector<int> seq) {
	vector<int> pos(seq.size(), 0);
	vector<int> neg(seq.size(), 0);
	int res = 1;
	for(int index = 0; index < seq.size(); ++index) {
		pos[index] = neg[index] = 1;

		for(int j = index - 1; j >= 0; j--) {
			int diff = seq[index] - seq[j];
			if(diff < 0 && (pos[j] + 1) > neg[index]) {
				neg[index] = pos[j] + 1;
				if(neg[index] > res) res = neg[index];
			}
			else if(diff > 0 && (neg[j] + 1) > pos[index]) {
				pos[index] = neg[j] + 1;
				if(pos[index] > res) res = pos[index];
			}
		}
	}
	
	return res;
}
		
void unitTests() {
	int t1[] = { 1, 7, 4, 9, 2, 5 }; // 6
	assert(longestZigZag(vector<int>(t1, t1+6)) == 6);
	int t2[] = { 1, 17, 5, 10, 13, 15, 10, 5, 16, 8 };
	assert(longestZigZag(vector<int>(t2, t2+10)) == 7);
	int t3[] = { 44 };
	assert(longestZigZag(vector<int>(t3, t3+1)) == 1);
	int t4[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	assert(longestZigZag(vector<int>(t4, t4+9)) == 2);
	int t5[] = { 70, 55, 13, 2, 99, 2, 80, 80, 80, 80, 100, 19, 7, 5, 
				 5, 5, 1000, 32, 32 };
	assert(longestZigZag(vector<int>(t5, t5+19)) == 8);
	int t6[] = { 374, 40, 854, 203, 203, 156, 362, 279, 812, 955, 
				 600, 947, 978, 46, 100, 953, 670, 862, 568, 188, 
				 67, 669, 810, 704, 52, 861, 49, 640, 370, 908, 
				 477, 245, 413, 109, 659, 401, 483, 308, 609, 120, 
				 249, 22, 176, 279, 23, 22, 617, 462, 459, 244 };
	assert(longestZigZag(vector<int>(t6, t6+50)) == 36);
}

int main(int argc, char *argv[]) {
	unitTests();
	return 0;
}

