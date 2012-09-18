// Problem F
// Maximum Sum II
// Input: standard input
// Output: standard output
// Time Limit: 1 second
//  
// In a given a sequence of non-negative integers you will have to find such 
// a sub-sequence in it whose summation is maximum.
//  
// Input
// The input file contains several input sets. The description of each set is 
// given below:
//  
// Each set starts with an integer N (N<1000) that indicates how many numbers 
// are in that set. Each of the next N lines contains a single non-negative 
// integer. All these numbers are less than 10000.
//  
// Input is terminated by a set where N=0. This set should not be processed.
//  
// Output
// For each set of input produce one line of output. This line contains one 
// or more integers which is are taken from the input sequence and whose 
// summation is maximum. If there is more than one such sub-sequence print 
// the one that has minimum length. If there is more than one sub-sequence 
// of minimum length, output the one that occurs first in the given sequence 
// of numbers. A valid sub-sequence must have a single number in it. Two 
// consecutive numbers in the output are separated by a single space.
//  
// Sample Input                               Output for Sample Input
// 2
// 3
// 4
// 0
// 3 4
//  
// Problem setter: Shahriar Manzoor, Member of Elite Problemsetters' Panel
// Special Thanks: Monirul Hasan, Member of Elite Problemsetters' Panel
// 
#include <stdio.h>

int N, allZero, entry;
int main(int argc, char *argv[])
{
	while(scanf(" %d", &N), N!=0)
	{
		allZero = 1;
		while(N--)
		{
			scanf(" %d", &entry);
			if(entry != 0) {
				if(!allZero)
					printf(" ");
				allZero = 0;
				printf("%d", entry);
			}
		}
		if(allZero) printf("0\n");
		else printf("\n");
	}
	return 0;
}
