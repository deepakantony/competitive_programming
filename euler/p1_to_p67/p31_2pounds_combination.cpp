#include <iostream>
#include <cstdlib>

using namespace std;

int count(int n) {
	int coins[] = {1,2,5,10,20,50,100,200};
	int m = sizeof(coins)/sizeof(int);
	
	int cnt[n+1];
	
	cnt[0] = 1;
	for(int i = 1; i <= n; i++)
		cnt[i] = 0;
		
	for(int j = 0; j < m; j++)
		for(int i = coins[j]; i <= n; i++)
			cnt[i] += cnt[i-coins[j]];
		
	return cnt[n];
}

int main(int argc, char **argv) {
	cout << count(atoi(argv[1])) << endl;

	return 0;
}
