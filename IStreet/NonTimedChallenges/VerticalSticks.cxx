// Vertical Sticks 
// 
// Given array of integers Y=y1,...,yn, we have n line segments such that 
// endpoints of segment i are (i, 0) and (i, yi). Imagine that from the top 
// of each segment a horizontal ray is shot to the left, and this ray stops 
// when it touches another segment or it hits the y-axis. We construct an 
// array of n integers, v1, ..., vn, where vi is equal to length of ray shot 
// from the top of segment i. We define V(y1, ..., yn) = v1 + ... + vn.
// 
// For example, if we have Y=[3,2,5,3,3,4,1,2], then v1, ..., 
// v8 = [1,1,3,1,1,3,1,2], as shown in the picture below:
// 
// see in the website!
// 
// For each permutation p of [1,...,n], we can calculate V(yp1, ..., ypn). 
// If we choose a uniformly random permutation p of [1,...,n], what is the 
// expected value of V(yp1, ..., ypn)?
// 
// Input Format
// 
// First line of input contains a single integer T (1 <= T <= 100). T test 
// cases follow.
// 
// First line of each test-case is a single integer N (1 <= N <= 50). Next 
// line contains positive integer numbers y1, ..., yN separated by a single 
// space (0 < yi <= 1000).
// 
// Output Format
// 
// For each test-case output expected value of V(yp1, ..., ypn), rounded to 
// two digits after the decimal point.
// 
// Sample Input
// 
// 6
// 
// 3
// 
// 1 2 3
// 
// 3
// 
// 3 3 3
// 
// 3
// 
// 2 2 3
// 
// 4
// 
// 10 2 4 4
// 
// 5
// 
// 10 10 10 5 10
// 
// 6
// 
// 1 2 3 4 5 6
// 
// Sample Output
// 
// 4.33
// 
// 3.00
// 
// 4.00
// 
// 6.00
// 
// 5.80
// 
// 11.15
// 
// Explanation
//  
// 
// Case 1: We have V(1,2,3) = 1+2+3 = 6, V(1,3,2) = 1+2+1 = 4, V(2,1,3) = 
// 1+1+3 = 5, V(2,3,1) = 1+2+1 = 4, V(3,1,2) = 1+1+2 = 4, V(3,2,1) = 1+1+1 = 3. 
// Average of these values is 4.33.
// Case 2: No matter what the permutation is, V(yp1, yp2, yp3) = 1+1+1 = 3, 
// so the answer is 3.00.
// Case 3: V(y1 ,y2 ,y3)=V(y2 ,y1 ,y3) = 5, V(y1, y3, y2)=V(y2, y3, y1) = 4, 
// V(y3, y1, y2)=V(y3, y2, y1) = 3, and average of these values is 4.00.
// 


#include <iostream>
#include <vector>

using namespace std;

// The idea is to solve each position at a time. Expected value for position 1
// is 1.0. Expected value for position >= 2, when you work through an example,
// it has some factorial values in it. Using the number of values >= and < than
// element currently being considered, we can work on a clever algorithm. I 
// found this algo online before I could discover it. That actually spoiled 
// the fun. Anywayz the solution is here.

double expectedValue(vector<int> V)
{
	double res = 1.0; // position 1 is precalculated
	int N = V.size();

	// calculate number of vals >= and < current entry
	vector<vector<int> > counter;
	for(int index = 0; index < N; ++index) 
	{
		int less = 0, more = 0;
		for(int index2 = 0; index2 < N; ++index2)
			if(index != index2) 
				if(V[index2] >= V[index])
					more++;
				else
					less++;
		vector<int> lessMore;
		lessMore.push_back(less);
		lessMore.push_back(more);
		counter.push_back(lessMore);
	}

	for(int position = 2; position <= N; ++position)
	{
		double posExpectedVal = 0.0;
		for(int index = 0; index < N; ++index)
		{
			int less = counter[index][0];
			int more = counter[index][1];

			double workingVal = 1.0;
			int workingPosition = 1;
			for(; workingPosition <= position-1; ++workingPosition)
			{
				posExpectedVal += (workingPosition * workingVal * 
								   ((double)more/(double)(less+more)));
				workingVal *= ((double)less/(double)(less+more));
				if(less-- == 0)
					break;
			}
			if(workingPosition == position)
				posExpectedVal += position*workingVal;
		}
		res += (posExpectedVal/N);
	}
	return res;
		
}

void solveVerticalSticks()
{
	int nTests;
	cin >> nTests;
	for(int test = 0; test < nTests; ++test)
	{
		int N;
		cin >> N;
		vector<int> V;
		for(int index = 0; index < N; ++index)
		{
			int val;
			cin >> val;
			V.push_back(val);
		}
		cout.setf(ios::fixed, ios::floatfield);
		cout.precision(2);
		cout << expectedValue(V) << endl;
	}
}

int main(int argc, char *argv[])
{
	solveVerticalSticks();
	return 0;
}
