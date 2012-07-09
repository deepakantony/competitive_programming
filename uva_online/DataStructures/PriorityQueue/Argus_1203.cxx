// A data stream is a real-time, continuous, ordered sequence of items. Some 
// examples include sensor data, Internet traffic, financial tickers, on-line 
// auctions, and transaction logs such as Web usage logs and telephone call 
// records. Likewise, queries over streams run continuously over a period of 
// time and incrementally return new results as new data arrives. For 
// example, a temperature detection system of a factory warehouse may run 
// queries like the following.
// 
// Query-1: “Every five minutes, retrieve the maximum temperature over the 
// past five minutes.” Query-2: “Return the average temperature measured on 
// each floor over the past 10 minutes.”
// We have developed a Data Stream Management System called Argus, which 
// processes the queries over the data streams. Users can register queries 
// to the Argus. Argus will keep the queries running over the changing data 
// and return the results to the corresponding user with the desired frequency.
// 
// For the Argus, we use the following instruction to register a query:
// 
// Register Q_num Period
// Q_num (0 < Q_num ≤ 3000) is query ID-number, and Period (0 < Period ≤ 
// 3000) is the interval between two consecutive returns of the result. 
// After Period seconds of register, the result will be returned for the 
// first time, and after that, the result will be returned every Period 
// seconds.
// 
// Here we have several different queries registered in Argus at once. It 
// is confirmed that all the queries have different Q_num. Your task is to 
// tell the first K queries to return the results. If two or more queries 
// are to return the results at the same time, they will return the results 
// one by one in the ascending order of Q_num.
// 
// Input 
// 
// The first part of the input are the register instructions to Argus, one 
// instruction per line. You can assume the number of the instructions will 
// not exceed 1000, and all these instructions are executed at the same 
// time. This part is ended with a line of “#”.
// 
// The second part is your task. This part contains only one line, which is 
// one positive integer K (≤ 10000).
// 
// Output 
// 
// You should output the Q_num of the first K queries to return the results, 
// one number per line.
// 
// Sample Input 
// 
// Register 2004 200
// Register 2005 300
// #
// 5
// Sample Output 
// 
// 2004
// 2005
// 2004
// 2004
// 2005

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#include <utility>

using namespace std;

#define QP pair<int, pair<int, int> >
#define REP(i, n) for(int (i) = 0; (i) < (n); ++i)
#define FOREACH(it, ctnr) for(__typeof__(ctnr.begin()) it = ctnr.begin(); it != ctnr.end(); ++it)

class ArgusComparison
{
public:
	bool operator () (const QP &x, const QP &y) {
		if(y.second.first < x.second.first) return true;
		if(y.second.first == x.second.first && 
		   y.second.second < x.second.second) return true;
		return false;
	}
};

int main(int argc, char *argv[])
{
	priority_queue<QP, vector<QP>, ArgusComparison> Q;
	char request[1001];
	int priority, period;
	scanf(" %s", request);
	while(request[0] != '#') {
		scanf(" %d", &priority);
		scanf(" %d", &period);
		Q.push(make_pair(period, make_pair(period, priority)));
		scanf(" %s", request);
	}

	int nQueries;
	QP cur;
	scanf(" %d", &nQueries);
	REP(query, nQueries) {
		cur = Q.top();
		printf("%d\n", cur.second.second);
		Q.pop();
		cur.second.first = cur.second.first + cur.first;
		Q.push(cur);
		
	}

	return 0;
}
