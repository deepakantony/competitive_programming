// I got the hint from here: http://ace.delos.com/TESTDATA/OPEN11.mowlawn.htm
// calculate partial sum psum[i] = profit[0..i]
// so the dp would be dp[i] = max[j=i-K to i](dp[j-1]+psum[i]-psum[j])
// i.e. maximum total with profit[j] removed

#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <utility>
#include <queue>

#define FOR(i,st,nd) for(int i = (st); i < (nd); ++i)
#define mp make_pair

using namespace std;
typedef long long int LL;
typedef pair<LL, int> PLI;

int main(int argc, char *argv[])
{
	vector<LL> profits, partial;
	priority_queue<PLI> maxLastK;

	int N, K; scanf(" %d %d", &N, &K);
	LL profit, sum = 0;

	FOR(i, 0, N) {
		scanf(" %lld", &profit);
		profits.push_back(profit);
		sum += profit;
		partial.push_back(sum);
	}

	vector<LL> dp(N, 0);
	// dp[i] = dp[j-1]+partial[i]-partial[j]; for j = i-K to i
	maxLastK.push(mp(0, -1));
	maxLastK.push(mp(-partial[0], 0));
	dp[0] = partial[0];
	FOR(i, 1, N) {
		while(maxLastK.top().second < (i-K))
			maxLastK.pop();
		maxLastK.push(mp(dp[i-1]-partial[i], i));

		dp[i] = partial[i] + maxLastK.top().first;
		
	}
	printf("%lld\n", dp[N-1]);
	return 0;
}
