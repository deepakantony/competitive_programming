// String Similarity
// 
// For two strings A and B, we define the similarity of the strings to be 
// the length of the longest prefix common to both strings. For example, 
// the similarity of strings "abc" and "abd" is 2, while the similarity 
// of strings "aaa" and "aaab" is 3.
// 
// Calculate the sum of similarities of a string S with each of it's suffixes.
// 
// Input:
// The first line contains the number of test cases T. Each of the next T 
// lines contains a string each.
// 
// Output:
// Output T lines containing the answer for the corresponding test case.
// 
// Constraints:
// 1 <= T <= 10
// The length of each string is at most 100000 and contains only lower case 
// characters.
// 
// Sample Input:
// 2
// ababaa
// aa
// 
// Sample Output:
// 11
// 3
// 
// Explanation:
// For the first case, the suffixes of the string are "ababaa", "babaa", 
// "abaa", "baa", "aa" and "a". The similarities of each of these strings 
// with the string "ababaa" are 6,0,3,0,1,1 respectively. Thus the answer 
// is 6 + 0 + 3 + 0 + 1 + 1 = 11.
// 
// For the second case, the answer is 2 + 1 = 3.
// 


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// solve this problem using Z Algorithm
// This algorithm calculates Z[i] containing the length of the common prefix
// at the suffix starting i.

typedef unsigned long long ullong;

void ZAlgorithm(const string &s, vector<int> &Z)
{
	Z.push_back(s.size());
	int R, L;
	R = L = 0;
	for(int i = 1; i < s.size(); ++i)
	{
		if(i > R) // need to find new R and L
		{
			L = R = i;
			while(R < s.size() && s[R-L] == s[R])
				++R;
			Z.push_back(R-L);
			--R;
		}
		else
		{
			if(Z[i-L] < R-i+1)
			{
				Z.push_back(Z[i-L]);
			}
			else
			{
				L = i;
				while(R < s.size() && s[R-L] == s[R])
					++R;
				Z.push_back(R-L);
				--R;
			}
		}
	}
}

ullong sumVec(vector<int> &vec)
{
	ullong sum = 0ull;
	for(auto it = vec.begin(); it != vec.end(); ++it)
		sum += *it;
	return sum;
}

int main(int argc, char *argv[])
{
	int nTests;
	cin >> nTests;
	for(int test = 0; test < nTests; ++test)
	{
		string curStr;
		cin >> curStr;
		vector<int> Z;
		ZAlgorithm(curStr, Z);
		cout << sumVec(Z) << endl;
	}
	return 0;
}

