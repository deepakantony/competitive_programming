//  Bridge Hand Evaluator 
// 
// In the card game ``Bridge'', players must assess the strength of their 
// hands prior to bidding against one another. Most players use a point-count 
// scheme which employs the following rules:
// 
// Each ace counts 4 points. Each king counts 3 points. Each queen counts 2
//  points. Each jack counts one point.
// Subtract a point for any king of a suit in which the hand holds no other 
// cards.
// Subtract a point for any queen in a suit in which the hand holds only 
// zero or one other cards.
// Subtract a point for any jack in a suit in which the hand holds only zero, 
// one, or two other cards.
// Add a point for each suit in which the hand contains exactly two cards.
// Add two points for each suit in which the hand contains exactly one card.
// Add two points for each suit in which the hand contains no cards.
// A suit is stopped if it contains an ace, or if it contains a king and at 
// least one other card, or if it contains a queen and at least two other 
// cards.
// 
// During the opening assessment, the three most common possibilities are:
// 
// If the hand evaluates to fewer than 14 points, then the player must pass.
// One may open bidding in a suit if the hand evaluates to 14 or more points. 
// Bidding is always opened in one of the suits with the most cards.
// One may open bidding in ``no trump'' if the hand evaluates to 16 or more 
// points ignoring rules 5, 6, and 7 and if all four suits are stopped. A no 
// trump bid is always preferred over a suit bid when both are possible.
// Input
// 
// Input to your program consists of a series of lines, each line containing 
// 13 cards. Each card consists of two characters. The first represents the 
// rank of the card: `A', `2', `3', `4', `5', `6', `7', `8', `9', `T', `J', 
// `Q', `K'. The second represents the suit of the card: `S', `H', `D', `C', 
// standing for ``spades'', ``hearts'', ``diamonds'', and ``clubs'', 
// respectively.
// 
// Output
// 
// For each line of the input, print one line containing the recommended bid, 
// either ``PASS'', the first ``BID suit'', where suit is ``S'', ``H'', 
// ``D'', or ``C'' (sorted in this natural way if two or more are possible), 
// or ``BID NO-TRUMP''.
// 
// For the first example below, the evaluation starts with 6 points for the 
// two kings, 4 for the ace, 6 for the three queens, and one for the jack. 
// To this tally of 17 points, we add 1 point for having only two cards in 
// spades, and subtract 1 for having a queen in spaces with only one other 
// card in spades. The resulting 17 points is enough to justify opening in a 
// suit.
// 
// The evaluation for no-trump is 16 points, since we cannot count the one 
// point for having only two spades. We cannot open in no-trump, however, 
// because the hearts suit is not stopped.
// 
// Hence we must open bidding in a suit. The two longest suits are clubs and 
// diamonds, with four cards each, so the possible outputs are ``BID C'', or 
// ``BID D''.
// 
// Sample Input
// 
// KS QS TH 8H 4H AC QC TC 5C KD QD JD 8D
// AC 3C 4C AS 7S 4S AD TD 7D 5D AH 7H 5H
// Sample Output
// 
// BID D
// BID NO-TRUMP

#include <cstdio>
#include <cstring>
#include <cstdlib>

#define REP(i, n) for(int (i) = 0; (i) < (n); ++i)
#define SD(n) scanf(" %d", &n)
#define SS(s) scanf(" %s", s)
#define intclear(v, sz) memset(v, 0, 4*sizeof(int))

int getSuitIndex(char suit) 
{
	switch(suit) {
	case 'S': return 0;
	case 'H': return 1;
	case 'D': return 2;
	} return 3;
}

int main(int argc, char *argv[]) 
{
	int stopped[4], count[4], king[4], queen[4], jack[4];
	char card[3];
	int score;
	int curSuit;
	while(!feof(stdin))
	{
		intclear(stopped, 4);
		intclear(count, 4);
		intclear(king, 4);
		intclear(queen, 4);
		intclear(jack, 4);
		score = 0;
		REP(i, 13) {
			SS(card);
			curSuit = getSuitIndex(card[1]);
			count[curSuit]++; 
			switch(card[0]) {
			case 'A': score += 4; stopped[curSuit] = 1; break;
			case 'K': score += 3; king[curSuit] = 1; break;
			case 'Q': score += 2; queen[curSuit] = 1; break;
			case 'J': score += 1; jack[curSuit] = 1; break;
			}
		}
		if(feof(stdin)) break;
		int allStopped = 1;
		int maxIndex = 0;
		int max = 0;
		REP(i, 4) {
			if(count[i] == 1 || count[i] == 0) score += 2;
			if(count[i] == 2) score++;
			if (king[i]) 
				if(count[i] > 1) stopped[i] = 1;
				else score--;
			if (queen[i])
				if (count[i] > 2) stopped[i] = 1;
				else score--;
			if (jack[i] && count[i] <= 3) score--;
			if(stopped[i] == 0) allStopped = 0;
			if(count[i] > max) {
				max = count[i];
				maxIndex = i;
			}
		}
		if(score < 14) 
			printf("PASS\n");
		else {
			printf("BID ");
			if(allStopped && score >= 16)
				printf("NO-TRUMP\n");
			else {
				switch(maxIndex) {
				case 0: printf("S\n"); break;
				case 1: printf("H\n"); break;
				case 2: printf("D\n"); break;
				case 3: printf("C\n"); break;
				}
			}
		}
			
		
	}
	return 0;
}
