#include <iostream>
#include <vector>
#include <queue> 
#include <functional>

using namespace std;

// I will use a priority_queue of size 4 to store the top 4 elements. This gives
// a complexity of O(N*log(4)) = O(N)
int main(int argc, char *argv[])
{
	int N; // number of integers
	cin >> N;

	priority_queue<int, vector<int>, greater<int> > Q; // make the heap minheap
	int curTerm;
	while(N-- && Q.size() != 4)
		cin >> curTerm, Q.push(curTerm);

	while(N>=0) {
		cin >> curTerm;
		if(curTerm > Q.top())
			Q.pop(), Q.push(curTerm);
		--N;
	}
	
	vector<int> topfour;
	while(!Q.empty())
		topfour.push_back(Q.top()), Q.pop();

	for(vector<int>::reverse_iterator it = topfour.rbegin(); 
		it != topfour.rend(); ++it)
		cout << *it << endl;
	
	return 0;
}


		
