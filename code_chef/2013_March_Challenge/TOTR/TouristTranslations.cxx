/*
  Problem: Tourist Translations
  Link: http://www.codechef.com/MARCH13/problems/TOTR
  Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
  Solution: establish mapping and convert
*/

#include <cstdio>
#include <cstring>
#include <cassert>
#include <ctime>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits>

using namespace std;

typedef unsigned long long UL;
typedef long long LL;
typedef pair<int,int> PII;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<LL> VL;
typedef vector<VL> VVL;
typedef vector<PII> VPII;
typedef vector<VPII> VVPII;

#define REP(i, n) for(int i = 0; i < (n); ++i)
#define FOR(i, st, nd) for(int i = (st); i < (nd); ++i)
#define SET(a, val) memset(a, val, sizeof(a))
#define mp make_pair

#define INF numeric_limits<int>::max()

void solve_tourist_translations()
{
	int length_of_converstaion;
	int sentence_index;
	int string_for_translation_index;
	char string_for_translation[101];
	char alphabet_mapping[27];

	scanf("%d%s", &length_of_converstaion, alphabet_mapping);

	REP(sentence_index, length_of_converstaion)
	{
		scanf("%s", string_for_translation);

		for(string_for_translation_index = 0;
			string_for_translation[string_for_translation_index];
			++string_for_translation_index
			)
		{
			if(string_for_translation[string_for_translation_index] == '_')
			{ // space
				string_for_translation[string_for_translation_index] = ' ';
			}
			else if(string_for_translation[string_for_translation_index] >= 'A'
					&& string_for_translation[string_for_translation_index] <= 'Z')
			{ // uppercase
				string_for_translation[string_for_translation_index] = 
					alphabet_mapping[string_for_translation[string_for_translation_index]-'A'] - 'a' + 'A';
			}
			else if(string_for_translation[string_for_translation_index] >= 'a'
					&& string_for_translation[string_for_translation_index] <= 'z')
			{ // lowercase
				string_for_translation[string_for_translation_index] = 
					alphabet_mapping[string_for_translation[string_for_translation_index]-'a'];
			}
			else
			{ // punctuations
			}
		}

		fprintf(stdout, "%s\n", string_for_translation);
	}
}

int main(int argc, char *argv[]) {
#ifndef ONLINE_JUDGE
	clock_t start = clock();
#endif 
	// solve something here
	solve_tourist_translations();

#ifndef ONLINE_JUDGE
	fprintf(stderr, "Time taken : %.5f seconds.\n",
			((float)clock()-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}
