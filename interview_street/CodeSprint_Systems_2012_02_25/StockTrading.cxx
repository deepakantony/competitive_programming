#include <iostream>
#include <vector>

using namespace std;
typedef unsigned long long ullong;

int getTheLastIncreasingSequenceIndex(const vector<ullong> &vec)
{
	for(int index = vec.size()-1; index > 0; --index)
	{
		if(vec[index] > vec[index-1])
			return index;
	}
	return -1;
}

int getIndexOfHigherValue(const vector<ullong> &vec, 
						  int startingIndex, 
						  ullong currentHighest)
{
	for(int index = startingIndex; index > 0; --index)
	{
		if(vec[index] > currentHighest && vec[index] > vec[index-1])
			return index;
	}
	return -1;
}

ullong findProfit(const vector<ullong> &vec, 
			   int topIndex, 
			   int endIndex,
			   ullong currentPrice)
{
	ullong profit = 0;
	for(int index = topIndex; index > endIndex; --index)
	{
		if(currentPrice > vec[index])
			profit += (currentPrice - vec[index]);
	}
	return profit;
}

ullong calculateProfit(const vector<ullong> &stockPrices)
{
	ullong profit = 0;
	int startingIndex = getTheLastIncreasingSequenceIndex(stockPrices);
	ullong currentPrice = 0;

	while(startingIndex > 0)
	{
		currentPrice = stockPrices[startingIndex];
		int currentIndex = startingIndex - 1;
		startingIndex = getIndexOfHigherValue(stockPrices, startingIndex,
											  currentPrice);
		profit += findProfit(stockPrices, 
							 currentIndex, 
							 startingIndex,
							 currentPrice);
	}
	return profit;
}

int main(int argc, char *argv[])
{
	int nTests;
	cin >> nTests;
	for(int test = 0; test < nTests; ++test)
	{

		int nDays;
		cin >> nDays;
		vector<ullong> stockPrices;
		for(int day = 0; day < nDays; ++day)
		{
			ullong price;
			cin >> price;
			stockPrices.push_back(price);
		}

		cout << calculateProfit(stockPrices) << endl;
	}

	return 0;
}
