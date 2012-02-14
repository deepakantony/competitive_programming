// Stone Piles : problem description
// 
// There are N piles of stones where the ith pile has xi stones in it. Alice 
// and Bob play the following game:
// 
// a. Alice starts, and they alternate turns.
// b. In a turn, a player can choose any one of the piles of stones and 
// divide the stones in it into any number of unequal piles such that no 
// two of the piles you create should have the same number of stones. For 
// example, if there 8 stones in a pile, it can be divided into one of these 
// set of piles: (1,2,5), (1,3,4), (1,7), (2,6) or (3,5). 
// c. The player who cannot make a move (because all the remaining piles are 
// indivisible) loses the game.
// 
// Given the starting set of piles, who wins the game assuming both players 
// play optimally?
// 
// Input:
// The first line contains the number of test cases T. T test cases follow. 
// The first line for each test case contains N, the number of piles 
// initially. The next line contains N space delimited numbers, the number 
// of stones in each of the piles.
// 
// Output:
// Output T lines, one corresponding to each test case containing "ALICE" 
// if Alice wins the game and "BOB" otherwise.
// 
// Constraints:
// 1 <= T <= 50
// 1 <= N <= 50
// 1 <= xi <= 50
// 
// Sample Input:
// 4
// 1
// 4
// 2
// 1 2
// 3
// 1 3 4
// 1
// 8
// 
// Sample Output:
// BOB
// BOB
// ALICE
// BOB
// 
// Explanation:
// For the first case, the only possible move for Alice is (4) -> (1,3). 
// Now Bob breaks up the pile with 3 stones into (1,2). At this point Alice 
// cannot make any move and has lost.
// 

// SOLUTION
//
// First problem is to find all the partition of a number. Look up number 
// partition (restricted and unrestricted). The paper http://www.site.uottawa.ca/~ivan/F49-int-part.pdf
// provides algorithm to generate all integer partitions (including ones
// containing duplicates). A small modification can produce non-duplicate 
// partitions. I used the algorithm from The Algorithm Manual - Steven S. Skiena
// section 8.3.6 - http://books.google.com/books?id=TrXd-gxPhVYC&printsec=frontcover&source=gbs_ge_summary_r&cad=0#v=onepage&q&f=false
// Some more links for more info on this:
// http://www.ics.uci.edu/~eppstein/PADS/IntegerPartitions.py
// 
// So, now that we have the partition, we need to find the winner. I did a bit
// cheating here; I got the logic from somewhere. In anycase here's the 
// description:
// Every integer's winning posibility is represented as binary number. If 
// there are 5 partitions of a number 5 bits will represent them. If a 
// partition wins, that partition will be 1 or else a 0. So for the number 5
// which has 2 partitions - (3,2) (4,1). we'll have 0 and 1. Since we need
// to represent this as a binary number and we'll use the smallest integer
// not present in the output of the partitions i.e. 2 in the above case which
// represents '10'. So next number, 6 has 3 partitions (5,1), (4,2) & (3,2,1);
// the output is 2, 0, and 1. This will be smallest integer greater than the
// output, which is 3 = '011' representing 1 loss and 2 wins. While the 
// integer, 8 has 5 partitions with all loses. So, the number will be '00000'.

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

vector<int> stonePile;

template<class vector_type>
void printVector(vector<vector_type> vec)
{
	copy(vec.begin(), vec.end(), ostream_iterator<vector_type>(cout, ","));
	cout << endl;
}

bool nextPartition(vector<int> &partition)
{
	int currentIndex = partition.size() - 1;
	while(true)
	{
		// Find the right most number in the partition which is greater than 2
	    while(currentIndex >= 0 && partition[currentIndex] <= 2)
		{
			currentIndex--;
		}
		if(currentIndex < 0)
			break;

		// Subtract 1 from it and try to add it in the rest of the numbers.
		// Compress the remaining number as much as possible keeping the 
		// numbers in descending order and no duplicates.
		int currentNumber = partition[currentIndex]-1;
		int remainder = 1;
		vector<int> newPartition;
		for(int index = 0; index < currentIndex; index++)
		{
			newPartition.push_back(partition[index]);
		}
		newPartition.push_back(currentNumber);
		for(int index = currentIndex + 1; index < partition.size(); index++)
		{
			remainder += partition[index];
		}
		currentNumber--;
		while(remainder > 0 && currentNumber > 0)
		{
			if( remainder >= currentNumber )
			{
			    newPartition.push_back(currentNumber);
				remainder -= currentNumber;
				currentNumber--;
			}
			else
			{
				newPartition.push_back(remainder);
				remainder = 0;
			}
		}

		// If you could not add 1, find the next number > 2
		// else point the currentIndex to the end of partition
		// If currentIndex is < 0 then all partitions have been identified
		if(remainder == 0)
		{
			partition.clear();
			copy(newPartition.begin(), newPartition.end(),
				 back_inserter(partition));
			newPartition.clear();
			return true;
		}
		else
		{
			currentIndex--;
			if (currentIndex < 0)
				break;
		}
	}
	return false;
}

void fillUpStonePile()
{
	stonePile = vector<int>(51);

	// basecases are all loses!
	stonePile[0] = 0;
	stonePile[1] = 0;
	stonePile[2] = 0;

	for(int pile = 3; pile < 51; ++pile)
	{
		vector<int> partition;
		partition.push_back(pile);
		int max = 0;
		vector<int> resultList;
		while(nextPartition(partition))
		{
			int result = stonePile[partition[0]];
			for(auto p = partition.begin()+1; p != partition.end(); ++p)
			{
				result ^= stonePile[*p];
			}
			resultList.push_back(result);
			if(result > max)
				max = result;
		}
		int winNumber = 0;
		// identify smallest integer not present in the result set
		for(int n = 0; n <= (max+1); n++)
			if(find(resultList.begin(), resultList.end(), n) == resultList.end())
			{
				winNumber = n;
				break;
			}
		stonePile[pile] = winNumber;
	}
}

int doIWin(vector<int> piles)
{
	int didWin = stonePile[piles[0]];
	for(auto pile = piles.begin() + 1; pile != piles.end(); ++pile)
		didWin ^= stonePile[*pile];
	return didWin;
}

int main(int argc, char *argv[])
{
	int nTests;
	cin >> nTests;

	fillUpStonePile();

	for(int test = 0; test < nTests; ++test)
	{
		int nPiles;
		cin >> nPiles;
		vector<int> pileSizes;

		for(int pile = 0; pile < nPiles; ++pile)
		{
			int pileSize;
			cin >> pileSize;
			pileSizes.push_back(pileSize);
		}

		if( doIWin(pileSizes) == 0 )
			cout << "BOB" << endl;
		else
			cout << "ALICE" << endl;
	}

	return 0;
}



