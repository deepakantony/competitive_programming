// List of Conquests
// Input: standard input
// Output: standard output
// Time Limit: 2 seconds
// 
// In Act I, Leporello is telling Donna Elvira about his master's long list 
// of conquests:
// 
// ``This is the list of the beauties my master has loved, a list I've made 
// out myself: take a look, read it with me. In Italy six hundred and forty, 
// in Germany two hundred and thirty-one, a hundred in France, ninety-one in 
// Turkey; but in Spain already a thousand and three! Among them are country 
// girls, waiting-maids, city beauties; there are countesses, baronesses, 
// marchionesses, princesses: women of every rank, of every size, of every 
// age.'' (Madamina, il catalogo è questo)
// 
// As Leporello records all the ``beauties'' Don Giovanni ``loved'' in 
// chronological order, it is very troublesome for him to present his 
// master's conquest to others because he needs to count the number of 
// ``beauties'' by their nationality each time. You are to help Leporello to 
// count.
// 
// Input
// 
// The input consists of at most 2000 lines, but the first. The first line 
// contains a number n, indicating that there will be n more lines. Each 
// following line, with at most 75 characters, contains a country (the first 
// word) and the name of a woman (the rest of the words in the line) Giovanni 
// loved. You may assume that the name of all countries consist of only one 
// word.
// 
// Output
// 
// The output consists of lines in alphabetical order. Each line starts with 
// the name of a country, followed by the total number of women Giovanni loved 
// in that country, separated by a space.
// 
// Sample Input
// 
// 3
// Spain Donna Elvira
// England Jane Doe
// Spain Donna Anna
// Sample Output
// 
// England 1
// Spain 2

#include <cstdio>
#include <map>
#include <string>

#define FOREACH(it, con) for(__typeof__(con.begin()) it = con.begin(); \
							 it != con.end(); ++it)

using namespace std;

int main(int argc, char *argv[]) 
{
	int n;
	scanf("%d", &n);
	char country[80], name[80];
	map<string, int> countryMap;
	for(int i = 0; i < n; i++)
	{
		scanf(" %s %[^\n]s", country, name);
		string c = string(country);
		map<string, int>::iterator it = countryMap.find(c);
		if(it != countryMap.end())
			it->second++;
		else
			countryMap[c] = 1;
	}

	FOREACH(it, countryMap) 
		printf("%s %d\n", it->first.c_str(), it->second);

	return 0;
}
