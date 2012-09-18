// I Can Guess the Data Structure!
// 
// There is a bag-like data structure, supporting two operations:
// 
// 1 x
// Throw an element x into the bag.
// 
// 2
// Take out an element from the bag.
// 
// Given a sequence of operations with return values, you're going to guess 
// the data structure. It is a stack (Last-In, First-Out), a queue (First-In, 
// First-Out), a priority-queue (Always take out larger elements first) or 
// something else that you can hardly imagine!
// 
// Input
// 
// There are several test cases. Each test case begins with a line 
// containing a single integer n (1<=n<=1000). Each of the next n lines is 
// either a type-1 command, or an integer 2 followed by an integer x. That 
// means after executing a type-2 command, we get an element x without error. 
// The value of x is always a positive integer not larger than 100. The 
// input is terminated by end-of-file (EOF). The size of input file does not 
// exceed 1MB.
// 
// Output
// 
// For each test case, output one of the following:
// 
// stack
// It's definitely a stack.
// 
// queue
// It's definitely a queue.
// 
// priority queue
// It's definitely a priority queue.
// 
// impossible
// It can't be a stack, a queue or a priority queue.
// 
// not sure
// It can be more than one of the three data structures mentioned above.
// 
// Sample Input
// 
// 6
// 1 1
// 1 2
// 1 3
// 2 1
// 2 2
// 2 3
// 6
// 1 1
// 1 2
// 1 3
// 2 3
// 2 2
// 2 1
// 2
// 1 1
// 2 2
// 4
// 1 2
// 1 1
// 2 1
// 2 2
// 7
// 1 2
// 1 5
// 1 1
// 1 3
// 2 5
// 1 4
// 2 4
// Output for the Sample Input
// 
// queue
// not sure
// impossible
// stack
// priority queue


#include <cstdlib>
#include <cstdio>
#include <stack>
#include <queue>

#define REP(i,n) for(int (i) = 0; (i) < (n); ++(i))

using namespace std;

int main(int argc, char *argv[])
{
	int N;
	while(scanf(" %d", &N) != EOF)
	{
		stack<int> st; queue<int> q; priority_queue<int> pq;
		bool isStack = true, isQueue = true, isPQ = true;
		REP(i, N) {
			int op, val;
			scanf(" %d %d", &op, &val);
			if(op == 1) {
				st.push(val); q.push(val); pq.push(val);
			}
			else if(op == 2) {
				if(st.empty() || st.top() != val) isStack = false;
				else st.pop();
				if(q.empty() || q.front() != val) isQueue = false;
				else q.pop();
				if(pq.empty() || pq.top() != val) isPQ = false;
				else pq.pop();
			}
		}
		if(!isStack && !isQueue && !isPQ)
			printf("impossible\n");
		else if( (isStack && isQueue) || (isStack && isPQ) || (isQueue && isPQ) )
			printf("not sure\n");
		else if(isStack)
			printf("stack\n");
		else if(isQueue)
			printf("queue\n");
		else printf("priority queue\n");
	}
	return 0;
}
