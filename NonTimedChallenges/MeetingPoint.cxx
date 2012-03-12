// Meeting Point (50 Points)
//  
// There is an infinite integer grid at which N people have their houses on. 
// They decide to unite at a common meeting place, which is someone's house. 
// From any given cell, all 8 adjacent cells are reachable in 1 unit of time. 
// eg: (x,y) can be reached from (x-1,y+1) in a single unit of time.
// Find a common meeting place which minimises the sum of the travel times of 
// all the persons.
// 
// Input Format:
// N
// The following N lines will contain two integers saying the x & y coordinate 
// of the i-th person.
// 
// Output Format:
// M M = min sum of all travel times; 
// 
// 
// Constraints:
// N <= 10^5
// The absolute value of each co-ordinate in the input will be atmost 109
// 
// HINT: Please use long long 64-bit integers;
// Input #00:
// 4
// 0 1
// 2 5
// 3 1
// 4 0
// 
// Output #00:
// 8
// 
// Explanation: Sums of travel times of the houses are 11, 13, 8 and 10. 8 is 
// the minimum.
// Input #01:
// 6
// 12 -14
// -3 3
// -14 7
// -14 -3
// 2 -12
// -1 -6
// Output #01:
// 54
// Note: Java/C# code should be in a class named "Solution"
// Read input from STDIN and write output to STDOUT
// 

#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

struct GridLocation 
{
	GridLocation() {}
	GridLocation(long long x, long long y) : x(x), y(y) {}
	long long x, y;
	void setxy(long long x, long long y) {
		this->x = x;
		this->y = y;
	}
	long long distance(const GridLocation &loc) const {
		long double xdiff = x - loc.x;
		long double ydiff = y - loc.y;
		return (long long) (floor(sqrt(xdiff*xdiff + ydiff*ydiff) + 0.5d));
	}
	long long chebyshevDistance(const GridLocation &loc) const {
		return max(abs(x-loc.x), abs(y-loc.y));
	}
	long double squareDist(long double &locX, long double &locY) const {
		long double xdiff = x - locX;
		long double ydiff = y - locY;
		return (xdiff * xdiff + ydiff * ydiff);
	}
	void print() {
		cout << x << " " << y << endl;
	}
};

void calculateAllDistances(GridLocation *locations, int nHouses)
{
	long long *distances = new long long[nHouses];

	for(int house = 0; house < nHouses; house++)
	{
		distances[house] = 0;
		for(int curHouse = 0; curHouse < house; curHouse++)
		{
			long long distance = locations[house].distance(locations[curHouse]);
			distances[curHouse] += distance;
			distances[house] += distance;
		}
	}

	for(int house = 0; house < nHouses; house++)
	{
		locations[house].print();
		cout << distances[house] << endl;
	}
}

void distanceToAllLocs(GridLocation *locations, int nHouses, GridLocation loc)
{
	for(int house = 0; house < nHouses; house++)
	{
		locations[house].print();
		cout << locations[house].chebyshevDistance(loc) << endl;
	}
}

int main()
{
	GridLocation *locations;

	int nHouses;
	cin >> nHouses;
	locations = new GridLocation[nHouses];

	// Input: all the grid locations
	// Calculate average while you're at it
	long double avgX = 0.d, avgY = 0.d;
	long long x, y;
	for( int house = 0; house < nHouses; house++ ) 
	{
		cin >> x >> y;
		avgX += ( ((long double)x)/nHouses );
		avgY += ( ((long double)y)/nHouses );
		locations[house].setxy(x,y);
	}

	// Find the Meeting house
	GridLocation meetingHouse = locations[0];
	long double smallestSqDist = locations[0].squareDist(avgX, avgY);
	for( int house = 1; house < nHouses; house++ )
	{
		long double newSqDist = locations[house].squareDist(avgX, avgY);
		if( smallestSqDist > newSqDist )
		{
			meetingHouse = locations[house];
			smallestSqDist = newSqDist;
		}
	}

//	meetingHouse.print();

	// Find the total distance to the meeting house
	long long totalDistance = 0;
	for( int house = 0; house < nHouses; house++ )
		totalDistance += locations[house].chebyshevDistance(meetingHouse);

	cout << totalDistance << endl;
	//calculateAllDistances(locations, nHouses);
	//distanceToAllLocs(locations, nHouses, meetingHouse);

	return 0;
}
