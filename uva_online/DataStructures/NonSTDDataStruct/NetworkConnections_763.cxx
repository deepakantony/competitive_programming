// Network Connections 
// Bob, who is a network administrator, supervises a network of computers. 
// He is keeping a log connections between the computers in the network. Each 
// connection is bi-directional. Two computers are interconnected if they are 
// directly connected or if they are interconnected with the same computer. 
// Occasionally, Bob has to decide, quickly, whether two given computers are 
// connected, directly or indirectly, according to the log information.
// 
// 
// Write a program which based on information input from a text file counts 
// the number of successful and the number of unsuccessful answers to the 
// questions of the kind :
// 
// 
// is computeri interconnected with computerj ?
// 
// Input and Output 
// 
// The first line of the input contains the number of dataset, and it's 
// followed by a blank line. Each dataset is defined as follows:
// 1.
// The number of computers in the network (a strictly positive integer);
// 2.
// A list of pairs of the form:
// (a)
// c computeri computerj, where computeri and computerj are integers from 
// 1 to  . A pair of this form shows that computeri and computerj get 
// interconnected.
// (b)
// q computeri computerj, where computeri and computerj are integers from 
// 1 to  . A pair of this form stands for the question: is computeri 
// interconnected with computerj?
// There's a blank line between datasets.
// 
// Each pair is on a separate line. Pairs can appear in any order, 
// regardless of their type. The log is updated after each pair of type (a) 
// and each pair of type (b) is processed according to the current network 
// configuration.
// 
// 
// For example, the input file illustrated in the sample below corresponds 
// to a network of 10 computers and 7 pairs. There are N1 successfully 
// answered questions and N2 unsuccessfully answered questions. The program 
// prints these two numbers to the standard output on the same line, in the 
// order: successful answers, unsuccessful answers, as shown in the sample 
// output. Print a blank line between datasets.
// 
// Sample Input 
// 
// 1
// 
// 10
// c 1 5
// c 2 7
// q 7 1
// c 3 9
// q 9 6
// c 2 5
// q 7 5
// Sample Input 
// 
// 1,2
// 


#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <vector>

#define REP(i,n) for(int (i) = 0; (i) < (n); ++i)
#define VI vector<int>

using namespace std;

class FindUnionSet
{
public:
	FindUnionSet(int n) {
		REP(i, n+1) { 
			parent.push_back(i);
			size.push_back(1);
		}
	}
	int findSet(int n) {
		if(parent[n] == n) return n;
		else return (parent[n] = findSet(parent[n]));
	}
	bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
	void unionSet(int i, int j) { 
		int si = findSet(i), sj = findSet(j);
		if(si == sj)
			return;
		else if(size[si] > size[sj]) {
			parent[sj] = si;
			size[si] += size[sj];
		}
		else {
			parent[si] = sj;
			size[sj] += size[si];
		}
	}
	void print() {
		REP(i, parent.size())
			printf("%d,", parent[i]);
		printf("\n");
	}
private:
	vector<int> parent;
	vector<int> size;
};

int main(int argc, char *argv[]) 
{
	int nDataSets, nComps, successfull, unsuccessfull;
	char line[100];
	scanf(" %d", &nDataSets);

	REP(i, nDataSets) 
	{
		successfull = unsuccessfull = 0;

		scanf(" %d\n", &nComps);
		FindUnionSet fus(nComps);
		char query;
		int c1, c2;
		
		while(fgets(line, 100, stdin) != 0 && line[0] != '\n') 
		{
			//printf( "%s", line);
			sscanf(line, " %c %d %d", &query, &c1, &c2);
			if(query == 'c') {
				fus.unionSet(c1, c2);
			}
			else if(fus.isSameSet(c1, c2))
				successfull++;
			else unsuccessfull++;
			//fus.print();
		}
		printf("%d,%d\n", successfull, unsuccessfull);
		if(i < nDataSets-1) printf("\n");
	}
	return 0;
}


