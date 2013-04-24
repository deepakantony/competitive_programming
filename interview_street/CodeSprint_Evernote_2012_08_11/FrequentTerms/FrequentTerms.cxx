// This problem is easily implemented with a map. The idea is check if the
// term exist; if so fetch the current count, remove the existing entry,
// increment the count and insert it back with the new count

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <utility>
#include <algorithm>
#include <functional>

using namespace std;

// This comparison function ensures lexicographical order of the terms when 
// frequency matches
bool compare(pair<int, string> term1, pair<int, string> term2) 
{
	if(term1.first == term2.first)
		return term1.second > term2.second;
	return term1.first < term2.first;
}

int main(int argc, char *argv[]) 
{
	map<string, int> termMap;
	
	int N; // number of terms
	cin >> N;
	
	string inputTerm;
	while(N--) {
		cin >> inputTerm;
		if(termMap.find(inputTerm) == termMap.end()) // inputTerm not found
			termMap[inputTerm] = 1;
		else
			termMap[inputTerm]++;
	}

	// stores the list of terms in decreasing order of it's frequency
	vector<pair<int,string> > termsQ; 

	for(map<string, int>::const_iterator it = termMap.begin(); 
		it != termMap.end(); ++it)
		termsQ.push_back( make_pair(it->second, it->first));
	make_heap(termsQ.begin(), termsQ.end(), compare);
	
	// How many terms to list
	int K;
	cin >> K;

	while(K-- && !termsQ.empty()) {
		cout << termsQ.front().second << endl;
		pop_heap(termsQ.begin(), termsQ.end(), compare);
		termsQ.pop_back();
	}

	
	
	return 0;
}
