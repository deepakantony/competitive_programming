#include <cstdio>
#include <cstring>

unsigned int freq[250];
unsigned int sums[251];
unsigned int memo[250][250];
int root[250][250];

// This algo uses knuths proof for the limit used for finding the position
// of the root
unsigned int optimalBST(int left, int right)
{

	if(memo[left][right] == -1) {
		if(left == right) {
			memo[left][right] = 0;
			root[left][right] = left;
		}
		else {
			// pos == left
			memo[left][right] = sums[right+1] - sums[left+1] + 
				optimalBST(left+1, right) ;
			root[left][right] = left;

			optimalBST(left, right-1);
			optimalBST(left+1, right);
			int lowerBound = root[left][right-1];
			if(lowerBound == left) lowerBound++;
			int upperBound = root[left+1][right];

			// lowerBound < pos < upperBound
			unsigned int curVal;
			for(int pos = lowerBound; pos < upperBound; pos++) {

				curVal = sums[pos] - sums[left] +
					optimalBST(left, pos-1) +
					sums[right+1] - sums[pos+1] + 
					optimalBST(pos+1, right);
				if(curVal < memo[left][right]) {
					memo[left][right] = curVal;
					root[left][right] = pos;
				}
			}
			// pos == right
			if(upperBound == right) {
				curVal = sums[right] - sums[left]
					+ optimalBST(left, right-1);
				if(curVal < memo[left][right]) {
					memo[left][right] = curVal;
					root[left][right] = right;
				}
			}
			else {
				curVal = sums[upperBound] - sums[left] +
					optimalBST(left, upperBound-1) +
					sums[right+1] - sums[upperBound+1] + 
					optimalBST(upperBound+1, right);
				if(curVal < memo[left][right]) {
					memo[left][right] = curVal;
					root[left][right] = upperBound;
				}

			}
				
		}
	}

	return memo[left][right];
}

int main(int argc, char *argv[])
{
	int sizeOfTree;
	sums[0] = 0;
	while(scanf(" %d", &sizeOfTree) != EOF) {
		for(int node = 0; node < sizeOfTree; node++) {
			scanf(" %d", &freq[node]);
			sums[node+1] = freq[node] + sums[node];
		}

		memset(memo, -1, sizeof memo);
		printf("%d\n", optimalBST(0, sizeOfTree-1));
	}
	return 0;
}
