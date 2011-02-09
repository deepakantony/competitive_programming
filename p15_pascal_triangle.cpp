#include <iostream>
#include <map>
#include <stack>
#include <vector>
#include <cstdlib>

using namespace std;

long long int combination(int n, int k) {
	if(n == k) return 1l;
	if(k == 0) return 1l;

	if(n > 0 && k > 0)
		return combination(n-1, k-1)*n/k;
	if(n > k)
		return combination(n-1, k)*n/(n-k);
	if(k > 0)
		return combination(n, k-1)*(n-k+1)/k;
}



int main(int argc, char *argv[]) {
	int n = atoi(argv[1]);
	cout << combination(2*n, n) << endl;

	return 0;
}
