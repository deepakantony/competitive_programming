#include <iostream>
#include <cstdlib>

using namespace std;

bool isleap(int year) {
	if(year%4 == 0)
		if(year%100 == 0 && year%400 != 0)
			return false;
		else
			return true;
	
	return false;
}

int year_starts_on(int year) {
	int starts_on = 1; // for 1900
	for(int y = 1900; y < year; y++) {
		if(isleap(y))	
			starts_on = (starts_on + 366)%7;
		else
			starts_on = (starts_on + 365)%7;
	}
	
	return starts_on;
}

int n_months_sunday(int from_year, int to_year) {
	int months[] = {31,28,31,30,31,30,31,31,30,31,30,31};
	
	int starts_on = year_starts_on(from_year);
	int count = 0;
	for(int year = from_year; year <= to_year; year++) {
		if(isleap(year)) months[1] = 29;
		else months[1] = 28;
		for(int i = 0; i < 12; i++) {
			if(starts_on == 0)
				count++;
			starts_on = (starts_on + months[i])%7;
		}
	}
	return count;
}


int main(int argc, char **argv) {
	cout << n_months_sunday(atoi(argv[1]), atoi(argv[2])) << endl;
	return 0;
}
