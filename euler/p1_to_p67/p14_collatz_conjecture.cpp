#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iterator>

using std::cout;
using std::endl;
using std::vector;

using namespace std;

int main(int argc, char *argv[]) {
	long limit = atol(argv[1]);
	long largest = 1;
	vector<long> series;
	series.push_back(1); // For 1 length of the series is 1
	for(long n = 2; n < limit; n++) {
		if(n%2 == 0) {
			series.push_back(1+series[(n/2) - 1]);
		}
		else {
			unsigned long long temp_n = n; // this will get modified
			unsigned long long length = 1;
			
			while( temp_n >= n) {
				if(temp_n%2 == 0)
					temp_n = temp_n/2;
				else
					temp_n = 3*temp_n + 1;
				length++;
			}
			
			series.push_back(length + series[temp_n-1]);
		}
		if(series[n-1] > series[largest-1])
			largest = n;
	}
	
	cout << largest << " " << series[largest-1] << endl;
	
	//ostream_iterator<int> out_it(cout, "\n");
	
	//copy(series.begin(), series.end(), out_it);
	
	return 0;
}	
