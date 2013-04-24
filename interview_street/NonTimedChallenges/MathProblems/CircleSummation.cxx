// Circle Summation 
// 
// There are N children sitting along a circle, numbered 1,2,...,N clockwise. 
// The ith child has a piece of paper with number ai written on it. They play 
// the following game:
// 
// In the first round, the child numbered x adds to his number the sum of 
// the numbers of his neighbors.
// In the second round, the child next in clockwise order adds to his number 
// the sum of the numbers of his neighbors, and so on.
// The game ends after M rounds have been played.
// 
// Input:
// The first line contains T, the number of test cases. T cases follow. The 
// first line for a test case contains two space seperated integers N and M. 
// The next line contains N integers, the ith number being ai.
// 
// Output:
// For each test case, output N lines each having N integers. The jth integer 
// on the ith line contains the number that the jth child ends up with if 
// the game starts with child i playing the first round. Output a blank line 
// after each test case except the last one. Since the numbers can be really 
// huge, output them modulo 1000000007.
// 
// Constraints:
// 1 <= T <= 15
// 3 <= N <= 50
// 1 <= M <= 10^9
// 1 <= ai <= 10^9
// 
// Sample Input:
// 2
// 5 1
// 10 20 30 40 50
// 3 4
// 1 2 1
// 
// Sample Output:
// 80 20 30 40 50
// 10 60 30 40 50
// 10 20 90 40 50
// 10 20 30 120 50
// 10 20 30 40 100
// 
//  
// 
// 23 7 12
// 11 21 6
// 7 13 24 
// 

// Read up on using matrix exponentiation to solve problems. Check out how to
// use matrix for efficiently finding the nth fibonacci number. Here's 
// a link: http://zobayer.blogspot.com/2010/11/matrix-exponentiation.html
// also checkout: http://forum.projecteuler.net/viewtopic.php?f=17&t=2444

#include <iostream>
#include <cstdio>
#include <vector>
#include <list>
#include <unordered_set>

using namespace std;

typedef unsigned long long ullong;

#define MOD_NUM 1000000007ull

class SquareMatrix {
public:
	SquareMatrix(int _size, int _exp) 
		: size(_size), exp(_exp) {
		//cout << _size << " " << _exp << endl;
		M = vector< vector<ullong> > (size, vector<ullong>(size, 0));
		orig = vector< vector<ullong> > (size, vector<ullong>(size, 0));
		initCircleSummation();
	}

	void multiply(const vector<ullong> &v, vector<ullong> & output) {
		output = vector<ullong>(v.size(), 0);
		for(int row = 0; row < size; ++row) 
			for(int col = 0; col < size; ++col) 
				output[row] =
					(output[row] + (M[row][col] * v[col])%MOD_NUM)
					%MOD_NUM;
	}

	void print() {
		for(int row = 0; row < size; ++row) {
			for(int col = 0; col < size; ++col)
				printf("%d ", M[row][col]);
			printf("\n");
		}
		printf("\n");
	}

private:
	void initCircleSummation() {
		// [ 0 1 0 0 ]   [ A1[n] ]   [ A2[n+1] ]
		// [ 0 0 1 0 ] X [ A2[n] ] = [ A3[n+1] ] 
		// [ 0 0 0 1 ]   [ A3[n] ]   [ A4[n+1] ]
		// [ 1 1 0 1 ]   [ A4[n] ]   [ A1[n+1] ]
		// all but last row changes :) read the problem again and reach this
		// matrix above (example uses 4x4).
		for(int index = 1; index < size; index++)
			orig[index-1][index] = M[index-1][index] = 1;
		M[size-1][0] = M[size-1][1] = M[size-1][size-1] = 1;
		orig[size-1][0] = orig[size-1][1] = orig[size-1][size-1] = 1;
		findExponential(exp);
	}
	
	void findExponential(int _exp) {
		
		if(_exp >= 2) {
			//cout << "I shouldnt come here" << _exp << endl;
			findExponential(_exp/2);
			multiplyWithItself();

			if(_exp % 2 == 1)
				multiplyWithOriginal();
		}
	}
	void multiplyWithItself() {
		vector<vector<ullong> > temp = 
			vector< vector<ullong> > (size, vector<ullong>(size, 0));		
		for(int row = 0; row < size; ++row)
			for(int col = 0; col < size; ++col) {
				for(int k = 0; k < size; ++k)
				    temp[row][col] = 
						(temp[row][col] + (M[row][k] * 
										   M[k][col] ) %MOD_NUM ) 
						% MOD_NUM;
			}

		for(int row = 0; row < size; ++row)
			for(int col = 0; col < size; ++col)
				M[row][col] = temp[row][col];
	}

	void multiplyWithOriginal() {
		vector<vector<ullong> > temp = 
			vector< vector<ullong> > (size, vector<ullong>(size, 0));		
		for(int row = 0; row < size; ++row)
			for(int col = 0; col < size; ++col) {
				for(int row2 = 0; row2 < size; ++row2)
				    temp[row][col] = 
						(temp[row][col] + (M[row][row2] * 
										   orig[row2][col] ) %MOD_NUM ) 
						% MOD_NUM;
			}
		for(int row = 0; row < size; ++row)
			for(int col = 0; col < size; ++col)
				M[row][col] = temp[row][col];
	}

	vector<vector<ullong> > M, orig;
	int size;
	int exp;
};

void print(vector<ullong> &vec, int n) {
	int index = 0; // used for printing space
	for(auto it = vec.begin() + vec.size() - n;
		it != vec.end(); ++it, ++index) {
		printf("%d", *it);
		if(index < vec.size()-1)
			printf(" ");
	}
	for(auto it = vec.begin(); 
		it != vec.begin() + vec.size() - n; ++it, ++index) {
		printf("%d", *it);
		if(index < vec.size()-1)
			printf(" ");
	}
}

void rotateBy1(vector<ullong> &vec) {
	list<ullong> rotated(vec.begin()+1, vec.end());
	rotated.push_back(vec[0]);
	vec.clear();
	vec = vector<ullong>(rotated.begin(), rotated.end());
}

void solveCircleSummation() {
	int nTests;
	scanf(" %d", &nTests);
	for(int test = 0; test < nTests; ++test) {
		int N;
		int mSize;
		scanf(" %d %d", &N, &mSize);
		
		vector<ullong> vec;
		for(int entry = 0; entry < N; ++entry) {
			int inp;
			scanf(" %d", &inp);
			vec.push_back(inp);
		}
		//printf("%d %d\n",N, mSize);
		SquareMatrix sqMat = SquareMatrix(N, mSize);
		int N_1 = mSize%N;
		vector<ullong> finalOut(N, 0);
		for(int entry = 0; entry < N; ++entry) {
			sqMat.multiply(vec, finalOut);
			print(finalOut, N_1);
			printf("\n");
			N_1 = (N_1 + 1) % N;
			rotateBy1(vec);
		}
		if(test < nTests -1)
			printf("\n");
	}
}

int main(int argc, char *argv[]) {
	solveCircleSummation();
	return 0;
}
