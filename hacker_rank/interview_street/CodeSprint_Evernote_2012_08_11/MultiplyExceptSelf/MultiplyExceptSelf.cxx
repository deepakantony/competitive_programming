#include <iostream>
#include <vector>

using namespace std;

typedef long long LL;

// Since only subset vector is said to be within 64bit integer, I will keep 1st 
// number out and calculate the product term[2]*...*term[N]. Then whenever I 
// need to calculate the next output, I divide by it and multiply the 1st term.
// Also, we need a special case for handling 0's in the list.
int main(int argc, char *argv[])
{
	int N; // number of elements.
	cin >> N;
	vector<LL> listOfElements;
	LL element, first;
	cin >> first; // first element
	N--;
	LL product = 1; // will contain the product term[2]*...*term[N]
	// number of zeroes in the list; if more than one, all the output is zero
	int numberOfZeroes = first==0 ? 1 : 0; // initial value
	while(N--) {
		cin >> element;
		if(element) // i.e. not zero
			product *= element;
		else numberOfZeroes++;
		listOfElements.push_back(element);
	}

	if(numberOfZeroes > 1) product = 0;

	
	// OUTPUT
	// For first terms output the product is displayed as is.
	if(numberOfZeroes == 1 && first != 0)
		cout << "0" << endl;
	else 
		cout << product << endl;
	// Output for the rest would be product*first/curElement

	for(int index = 0; index < listOfElements.size(); ++index)
		if(listOfElements[index] != 0)
			if(numberOfZeroes == 1)
				cout << "0" << endl;
			else
				cout << (product/listOfElements[index])*first << endl;
		else 
			cout << product*first << endl;

	return 0;
}
