#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

/*typedef enum _player {
	player1,
	player2,
	undecided
	} Player;*/
// #define player1 0
// #define player2 1
// #define undecided 2
// typedef int Player;

#define LOSER 0
#define WINNER 1
#define UNDECIDED 2

vector<int> stonePile;

template<class vector_type>
void printVector(vector<vector_type> vec)
{
	copy(vec.begin(), vec.end(), ostream_iterator<vector_type>(cout, ","));
	cout << endl;
}

int flip(int p)
{
	return !p;
}

int stonePileWinner(int N)
{
	if(N == 1)
	{
		stonePile[N-1] = LOSER;
		return LOSER;
	}

	if(N == 2)
	{
		stonePile[N-1] = LOSER;
		return LOSER;
	}

	vector<int> partition;
	partition.push_back(N);

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
			currentIndex = partition.size() - 1;
			printVector(partition);
			int w;
			if(stonePile[partition[0]-1] == UNDECIDED)
				w = stonePileWinner(partition[0]);
			else
				w = stonePile[partition[0]-1];
			cout << partition[0] << " " << w << endl;
			for(auto it = (partition.begin() + 1); it != partition.end(); ++it)
			{
				if(stonePile[(*it)-1] == UNDECIDED)
					w ^= (stonePileWinner(*it));
				else
					w ^= (stonePile[(*it)-1]);
				cout << *it << " " << w << endl;
			}

			cout << "Final: " << w << endl;

			if(w)
			{
				stonePile[N-1] = WINNER;
				return WINNER;
			}
		}
		else
		{
			currentIndex--;
			if (currentIndex < 0)
				break;
		}
	}
	stonePile[N-1] = LOSER;
	return LOSER;
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
	stonePile = vector<int>(51, UNDECIDED);
	stonePile[1] = LOSER;
	stonePile[2] = LOSER;

	for(int pile = 3; pile < 51; ++pile)
	{
		vector<int> partition;
		partition.push_back(pile);
		while(nextPartition(partition))
		{
			int iLose = stonePile[partition[0]];
			for(auto p = partition.begin()+1; p != partition.end(); ++p)
			{
				iLose ^= stonePile[*p];
			}
			if(!iLose)
			{
				stonePile[pile] = WINNER;
				break;
			}
		}
		if(stonePile[pile] == UNDECIDED)
			stonePile[pile] = LOSER;
	}
}

bool doIWin(vector<int> piles)
{
	bool didWin = stonePile[piles[0]];
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

		if( doIWin(pileSizes) )
			cout << "ALICE" << endl;
		else
			cout << "BOB" << endl;
	}

	return 0;
}



