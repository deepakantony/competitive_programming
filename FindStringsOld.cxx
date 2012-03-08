#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

// Convert string to char; but normalized (so subtract 'a' from it; start from 1)
void convertStringToIntChar(const string &str, int *output)
{
	int index = 0;
	for(auto it = str.begin(); it != str.end(); ++it) 
	{
		output[index++] = 1 + (int)(*it) - (int)'a';
#ifdef _DBUG
		cout << *it << "," << index-1;
#endif
	}
#ifdef _DBUG
	cout << endl;
#endif
	output[str.size()] = output[str.size()+1] = output[str.size()+2] = 0;
}

// using the source code from the paper: Linear Work suffix array construction

// Lexicographic order for pairs
template<class pair_type1, class pair_type2>
bool leq(pair_type1 a1, pair_type2 a2, pair_type1 b1, pair_type2 b2)
{
	return (a1 < b1 || (a1 == b1 && a2 < b2));
}

// Lexicographic order for triplets
template<class triplet_type1, class triplet_type2>
bool leq(triplet_type1 a1, triplet_type1 a2, triplet_type2 a3,
		 triplet_type1 b1, triplet_type1 b2, triplet_type2 b3)
{
	return (a1 < b1 || (a1 == b1 && leq(a2, a3, b2, b3)));
}

// triplet equals check
template<class triplet_type>
bool tripletEquals(triplet_type a, triplet_type b)
{
	return (a[0] == b[0] && a[1] == b[1] && a[2] == b[2]);
}

// assign a triplet 
template<class triplet_type>
void tripletAssign(triplet_type a, triplet_type b)
{
	b[0] = a[0]; b[1] = a[1]; b[2] = a[2];
}

// Stably sort the an array[0..n-1] to output[0..n-1] using the keys or
// normalized alphabets within 0..K from sourceArray. We use the 0 for invalid 
// alphabets, like for extending the string to be a multiple of 0 and etc...
// In any case 0 should never occur in this sort, since n will always be < 
// length of the actual string.
//
// Lets work through an example - sorting "abdaba" in linear time.
// sourceArray = {1, 2, 4, 1, 2, 1} // normalized string[i] - 'a' + 1
// array = {0, 1, 2, 3, 4, 5} // unsorted
// output = {0, 3, 5, 1, 4, 2} // sorted
template<class element_type, class index_type>
void radixPass(index_type *array, index_type *output, 
			   element_type *sourceArray, index_type n, element_type K)
{
	// initialize counter
	// counter = {0, 0, 0, 0, 0} // assuming K = 4 for only a, b, c and d
	index_type *counter = new index_type[K+1];
	fill(counter, counter+K+1, 0);

	// Count occurences
	// counter = {0, 3, 2, 0, 1}
	for(auto index = 0; index < n; ++index)
		counter[sourceArray[array[index]]]++;

	// exclusive prefix sums; essentially identify the indices that each 
	// element will start.
	// counter = {0, 0, 3, 5, 5}, what it means is 'a' will appear at position 0
	// till 'b' occurs; 'b' will start at position 3 till 'c'; since there is 
	// no 'c', 'd' will be put at position '5'
	for(auto index = 0, sum = 0; index <= K; ++index)
	{
		auto temp = counter[index];
		counter[index] = sum;
		sum += temp;
	}

	// now put the sorted array back to output
	// output = {0, 3, 5, 1, 4, 2}
	for(auto index = 0; index < n; ++index)
	{
		output[counter[sourceArray[array[index]]]++] = array[index];
		// the increments to counter is the way of keeping the counter pointing
		// rightly to the index where I would assign that element.
	}

	// release counter
	delete [] counter;
}

// Recursively find the suffixArray from the inputArray[0..n-1](normalized string 
// usually) in [1..K].
// Requires inputArray[n] = inputArray[n+1] = inputArray[n+2] = 0, for n >= 2
//
// This one is a tough one to follow easily, let me use an example
// our string = "yabbadabbado"
// inputArray = { y a b b a d a b b a d  o  } // normalized (inputArray[i] - 'a' + 1
//                0 1 2 3 4 5 6 7 8 9 10 11
// so, n = 12, size of input array
// K = 26, all are english characters
// expected output:
// suffixArray= { 6  abbado
//                1  abbadabbado
//                4  adabbado
//                9  ado
//                3  badabbado
//                8  bado
//                2  bbadabbado
//                7  bbado
//                5  dabbado
//                10 do
//                11 o
//                0  yabbadabbado }
//
template<class element_type, class index_type>
void constructSuffixArray(element_type *inputArray, index_type *suffixArray,
						  index_type n, element_type K)
{
	// size of n%3 == 0 = n0, n%3 == 1 = n1 and n%3 == 2 = n2
	// for our case n0 = 4, n1 = 4, n2 = 4, n02 = 8
	int n0 = (n+2)/3, n1 = (n+1)/3, n2 = n/3, n02 = n0 + n2; 
	// similarly s0, s1, and s2 are indices pointing to s such that
	// i%3 == 0 for s0, i%3 == 1 for s1 and i%3 == 2 for s2. 
	// now create s12, a concatenation of s1 and s2 (note: we can directly 
	// create s12)
	int *s12 = new int[n02 + 3]; // s12.size() = 11
	int *SA12 = new int[n02 + 3]; // SA12.size() = 11
	s12[n02] = s12[n02+1] = s12[n02+2] = 0; // s12[8,9,10] = 0
	SA12[n02] = SA12[n02+1] = SA12[n02+2] = 0; // SA12[8,9,10] = 0
	int *s0 = new int[n0];
	int *SA0 = new int[n0];

	// Initialize s12, for our example s12 = [ 1 2 4 5 7 8 10 11 0 0 0 ]
	// so s12 is { [abb][ada][bba][do0][bba][dab][bad][o00] } not in the 
	// right order, but you get the idea
	for(auto index = 0, indexS12 = 0; index < n + (n0 - n1); ++index)
		if( index%3 != 0)
			s12[indexS12++] = index; 


	cout << "First radix pass" << endl;

	// Sort the triplets
	// For our example...
	radixPass(s12, SA12, inputArray + 2, n02, K);
	// in the first radix pass i'm comparing s12 = { 1 2 4 5 7 8 10 11 } + 2
	// { 3 4 6 7 9 10 12 13 } is the actual indices in inputArray that is 
	// compared. the alphabets compared are { b a a b a d 0 0 }
	// SA12 = { 12 13 4 6 9 3 7 10 } - 2 = { 10 11 2 4 7 1 5 8 } 
	cout << "Second radix pass" << endl;
	radixPass(SA12, s12, inputArray + 1, n02, K);
	// second radix pass we're comparing SA12 + 1 = { 11 12 3 5 8 2 6 9 }
	// the alphabets compared are { o 0 b d b b a a }
	// so s12 = { 12 6 9 3 8 2 5 11 } - 1 = { 11 5 8 2 7 1 4 10 }
	cout << "Third radix pass" << endl;
	radixPass(s12, SA12, inputArray, n02, K);
	// third radix pass we're comparing s12 = { 11 5 8 2 7 1 4 10 }
	// the alphabets compared are { o d b b b a a d }
	// so SA12 = { 1 4 8 2 7 5 10 11 }
	// i.e. SA12 = { [abb][ada][bad][bba][bba][dab][do0][o00] }

	// find lexicographic names of triples
	// So at the end of this loop name = 7, since there is duplicate
	// triplet [bba]
	int name = 0;
	element_type *prev = new element_type[3];
	fill(prev, prev+2, -1);
	for(auto index = 0; index < n02; index++)
	{
		if( ! tripletEquals(prev, inputArray+index) )
		{
			name++;
			tripletAssign(inputArray+index, prev);
		}
		if( SA12[index] % 3 == 1 )
			s12[SA12[index]/3] = name; // left half
		else
			s12[SA12[index]/3 + n0] = name; // right half
		// at the end of the loop our examples s12 will be
		// { 1 2 4 6 3 4 5 7 }
	}

	// recurse if names are not unique
	if ( name < n02) // for our example this is true
	{
		// So, we're finding suffix array of {1 2 4 6 3 4 5 7}
		//                                    0 1 2 3 4 5 6 7
		// after this recursion the SA12 = [ 0 1 4 5 2 6 3 7 ]
		constructSuffixArray(s12, SA12, n02, name);
		// store unique names in s12 using the suffix array
		for(int index = 0; index < n02; ++index)
			s12[SA12[index]] = index + 1;
		// our s12 will be s12 = [1 2 5 7 3 4 6 8 
		//                        0 1 2 3 4 5 6 7
	}
	else
	{ // generate the suffix array of s12 directly
		for(int index = 0; index < n02; ++index)
			SA12[s12[index] - 1] = index;
	}

	// stably sort mod 0 suffixes from SA12 by their first character
	// for our example s0 = [ 0 3 6 9 ] = [ y b a a ]
	for(auto index = 0, indexS0 = 0; index < n02; ++index)
		if(SA12[index] < n0)
			s0[indexS0++] = 3*SA12[index];
	// after the radix pass SA0 = [ 6 9 3 0 ]
	cout << "Fourth radix pass" << endl;
	radixPass(s0, SA0, inputArray, n0, K);

	cout << "All radix passes done" << endl;

	// merge sorted SA0 suffixes and sorted SA12 suffixes
	for(int indexS0 = 0, indexS12 = 0, index = 0; index < n; ++index)
	{
		auto curPos12 = (SA12[indexS12] < n0) ?  
			SA12[indexS12] * 3 + 1 : (SA12[indexS12] - n0) * 3 + 2;
		auto curPos0 = SA0[indexS0];
		if( SA12[indexS12] < n0 ? 
			leq(inputArray[curPos12],  s12[SA12[indexS12] + n0], 
				inputArray[curPos0], s12[curPos0/3]) :
			leq(inputArray[curPos12], inputArray[curPos12+1], s12[SA12[indexS12]-n0+1],
				inputArray[curPos0], inputArray[curPos0+1], s12[curPos0/3 + n0]))
		{
			suffixArray[index] = curPos12;
			indexS12++;
			if(indexS12 == n02) // done -- only SA0 suffixes left
			{
				for(index++; indexS0 < n0; ++indexS0, ++index)
					suffixArray[index] = SA0[indexS0];
			}
		}
		else
		{
			suffixArray[index] = curPos0;
			indexS0++;
			if(indexS0 == n0) // done -- only SA12 suffixes left
			{
				for(index++; indexS12 < n02; ++indexS12, ++index)
					suffixArray[index] = (SA12[indexS12] < n0) ?  
						SA12[indexS12] * 3 + 1 : (SA12[indexS12] - n0) * 3 + 2;
			}
		}			   
	}

	cout << "suffix array calculated" << endl;

	delete [] s12;
	delete [] SA12;
	delete [] SA0;
	delete [] s0;
}

template<class container_type>
void printContainer(container_type c)
{
	cout << "( ";
	for(auto it = c.begin(); it != c.end(); ++it)
		cout << *it << " ,";
	cout << " )" << endl;
}

template<class iterator_type>
void printContainer(iterator_type left, iterator_type right)
{
	cout << "( ";
	for(iterator_type it = left; it != right; ++it)
		cout << (int)*it << ", ";
	cout << " )" << endl;
	
}

class SuffixArray
{
public:
	SuffixArray(); // default initialization for adding strings later
	SuffixArray(const string &inpStr); // init with a string

	void add(const string &inpStr);
	void updateVector();
	void updateSubstringVec();
	string substring(long long idx);
	string substringBinSearch(long long idx);
	void print() const;
	void printSubstrings() const;
private:
	void updateSuffixArray(const string &inpStr);

	struct SANode 
	{
		SANode() 
			: leftIndex(-1), strIdx(-1), lcp(0), index(0){}
		SANode(vector<string> *sl) 
			: leftIndex(-1), strIdx(-1), lcp(0), index(0) {}
		int strIdx; // string index
		int leftIndex; // starting position of the suffix
		int lcp; // longest common prefix
		long long index; // when queried this will be used to do the binary search
	};

	bool nodeLT(const SANode &node1, const SANode &node2) const;
	bool nodeEQ(const SANode &node1, const SANode &node2) const;
	int findLCP(const SANode &prev, const SANode &cur) const;
	bool nodeHasStringIndex(const SANode &node, long long idx) const;
	bool nodeIsLTIndex(const SANode &node, long long idx) const;
	string constructStringInNode(const SANode &node, int prefixIndex) const;

	struct NodeCmp
	{
		NodeCmp(vector<string> &sl) : stringList(sl) {}
		bool operator() (const SANode &ths, const SANode &other) const; // this will be used by set for sorting	
		vector<string> &stringList;
	} nc;
	void printNode(const SANode &node) const;

	set<SANode,NodeCmp> suffixSet; // this eliminates duplicates
	vector<SANode> suffixVec; // random access
	long long substringsMaxIndex; // number of distinct substrings - 1
	vector<string> stringList; // list of strings and suffixs
	vector<SANode> sortedSuffixSet; // constructed using linear suffix array algo

	struct SNode // substring node
	{
		SNode(int idx, int l, int r) : strIdx(idx), left(l), right(r) {}
		int strIdx;
		int left, right;
	};
	string constructSubstring(const SNode &node) const;
	void addAllSubstrings(const SANode &node);
	vector<SNode> substringVec;
};

SuffixArray::SuffixArray()
	: nc(stringList), suffixSet(nc)
{
}

SuffixArray::SuffixArray(const string &inpStr)
	: nc(stringList), suffixSet(nc)
{
	updateSuffixArray(inpStr);
}

void SuffixArray::add(const string &inpStr)
{
	updateSuffixArray(inpStr);
}

void SuffixArray::updateVector()
{
	suffixVec.clear();
	if(suffixSet.empty())
		return;

	// add it to the vector
	suffixVec.push_back(*suffixSet.begin());
	auto it = suffixSet.begin();
	SANode prev = *it;
	SANode cur;
	++it;
	while(it != suffixSet.end())
	{
		cur = *it;
		cur.lcp = findLCP(prev, cur);
		cur.index = 0ll + prev.index + stringList[prev.strIdx].size() - 
			(prev.lcp + prev.leftIndex);
		suffixVec.push_back(cur);

		prev = cur;
		++it;
	}
	substringsMaxIndex = 0ll + prev.index + stringList[prev.strIdx].size() - 
			(prev.lcp + prev.leftIndex) - 1ll;
}

void SuffixArray::updateSubstringVec()
{
	substringVec.clear();
	if(sortedSuffixSet.empty())
		return;
	addAllSubstrings(*sortedSuffixSet.begin());
	auto it = sortedSuffixSet.begin();
	SANode prev = *it;
	SANode cur;
	++it;
	while(it != sortedSuffixSet.end())
	{
		cur = *it;
		cur.lcp = findLCP(prev, cur);
		cur.index = 0ll + prev.index + stringList[prev.strIdx].size() - 
			(prev.lcp + prev.leftIndex);
		addAllSubstrings(cur);

		prev = cur;
		++it;
	}
}

void SuffixArray::addAllSubstrings(const SANode &node)
{
	for(int rightIndex = node.leftIndex + node.lcp + 1;
		rightIndex <= stringList[node.strIdx].size(); ++rightIndex)
		substringVec.push_back(SNode(node.strIdx, node.leftIndex, rightIndex));
}

string SuffixArray::substring(long long idx)
{
	if(idx < 0 || idx >= substringVec.size())
		return string("INVALID");
	return constructSubstring(substringVec[idx]);
}

string SuffixArray::constructSubstring(const SNode &subNode) const
{
	string res;
	for(auto it = stringList[subNode.strIdx].begin() + subNode.left;
		it != stringList[subNode.strIdx].begin() + subNode.right; ++it)
		res += *it;
	return res;
}

string SuffixArray::substringBinSearch(long long idx)
{
	if(idx < 0 || idx > substringsMaxIndex)
		return string("INVALID");

	string res;
	// binary search the suffixVec for the substring[idx]
	long long left = 0;
	long long right = suffixVec.size();
	long long middle = left + (right - left)/2;
	while(left < right)
	{
		if(nodeHasStringIndex(suffixVec[middle], idx))
		{
			int prefixIndex = idx - suffixVec[middle].index + 
				suffixVec[middle].leftIndex + suffixVec[middle].lcp + 1;
			//cout << prefixIndex << endl;
			res = constructStringInNode(suffixVec[middle], prefixIndex);
			break;
		}
		else if (nodeIsLTIndex(suffixVec[middle], idx))
		{
			left = middle + 1;
		}
		else 
		{
			right = middle;
		}
		middle = left + (right - left)/2;
	}
	return res.size() > 0 ? res : string("INVALID");
}

void SuffixArray::print() const
{
	for(auto it = suffixVec.begin(); it != suffixVec.end(); ++it)
		printNode(*it);
}

void SuffixArray::printSubstrings() const
{
	for(auto it = substringVec.begin(); it != substringVec.end(); ++it)
		cout << constructSubstring(*it) << endl;
}

void SuffixArray::updateSuffixArray(const string &inpStr)
{
	int curIndex = stringList.size();
	stringList.push_back(inpStr);
	cout << inpStr << endl;
	// convert to normalized char*
	int *inpStrChar = new int[inpStr.size()+3];;
	convertStringToIntChar(inpStr, inpStrChar);

	printContainer(inpStrChar, inpStrChar+inpStr.size());

	int *suffixArray = new int[inpStr.size()];
	int K = 26; // 26 english chars supported

	constructSuffixArray(inpStrChar,  suffixArray, (int)inpStr.size(), K); 
	printContainer(suffixArray, suffixArray+inpStr.size());
	vector<SANode> tempSortedSet(sortedSuffixSet.begin(), sortedSuffixSet.end());
	sortedSuffixSet.clear();
	cout << "Sorting and merging begins" << endl;
	auto it_temp = tempSortedSet.begin();
	for(auto index = 0; index < inpStr.size(); ++index)
	{
		SANode newNode;
		newNode.strIdx = curIndex;
		newNode.leftIndex = suffixArray[index];
		
		while(it_temp != tempSortedSet.end() && nodeLT(*it_temp, newNode))
		{
			sortedSuffixSet.push_back(*it_temp);
			++it_temp;
		}
		if( (it_temp != tempSortedSet.end() && !nodeEQ(*it_temp, newNode)) 
			|| (it_temp == tempSortedSet.end()))
		{
			sortedSuffixSet.push_back(*it_temp);
		}
	}
	for(;it_temp != tempSortedSet.end(); ++it_temp)
		sortedSuffixSet.push_back(*it_temp);
	cout << "Sofrting and merging complete" << endl;
/* // old sequential method
	int curIndex = stringList.size();
	stringList.push_back(inpStr);
	for(int leftIndex = 0; leftIndex < inpStr.size(); ++leftIndex)
	{
		SANode newNode(&stringList);
		newNode.strIdx = curIndex;
		newNode.leftIndex = leftIndex;
		suffixSet.insert(newNode);
	}
*/
}

int SuffixArray::findLCP(const SANode &prev, const SANode &cur) const
{
	int LCP = 0;
	for(auto it_this = stringList[prev.strIdx].begin()+prev.leftIndex,
			it_other = stringList[cur.strIdx].begin()+cur.leftIndex;
		it_this != stringList[prev.strIdx].end() || 
			it_other != stringList[cur.strIdx].end(); 
		++it_this, ++it_other)
	{
		if(*it_this == *it_other)
			++LCP;
		else
			break;
	}

	return LCP;
}

bool SuffixArray::nodeHasStringIndex(const SANode &node, long long idx) const
{
	if (node.index <= idx && 
		(node.index + stringList[node.strIdx].size() 
		 - node.leftIndex - node.lcp) > idx)
		return true;
	// else
	return false;
		
}

bool SuffixArray::nodeIsLTIndex(const SANode &node, long long idx) const
{
	return node.index < idx;
}

string SuffixArray::constructStringInNode(const SANode &node, int prefixIndex) const
{
	string res;
	for(auto it = stringList[node.strIdx].begin() + node.leftIndex;
		it != stringList[node.strIdx].begin() + prefixIndex; ++it)
		res += *it;

	return res;
}

bool SuffixArray::nodeLT(const SANode &node1, const SANode &node2) const
{
	return nc(node1, node2);
}

bool SuffixArray::nodeEQ(const SANode &node1, const SANode &node2) const
{
	auto node1Size = stringList[node1.strIdx].size() - node1.leftIndex;
	auto node2Size = stringList[node2.strIdx].size() - node2.leftIndex;

	if(node1Size != node2Size)
		return false;
	else
	{
		for(auto it_node1 = stringList[node1.strIdx].begin()+node1.leftIndex,
				it_node2 = stringList[node2.strIdx].begin()+node2.leftIndex;
			it_node1 != stringList[node1.strIdx].end() && 
				it_node2 != stringList[node2.strIdx].end(); 
			++it_node1, ++it_node2)
		{
			if(*it_node1 != *it_node2)
				return false;
		}
	}
	return true;
}


bool SuffixArray::NodeCmp::operator()(const SANode &ths, const SANode &other) const
{
	for(auto it_this = stringList[ths.strIdx].begin()+ths.leftIndex,
			it_other = stringList[other.strIdx].begin()+other.leftIndex;
		it_this != stringList[ths.strIdx].end() && 
			it_other != stringList[other.strIdx].end(); 
		++it_this, ++it_other)
	{
		if(*it_this > *it_other)
		{
			return false;
		}
		else if(*it_this < *it_other)
		{
			return true;
		}
	}

	return (stringList[ths.strIdx].size() - ths.leftIndex < 
			stringList[other.strIdx].size() - other.leftIndex) ? true : false;

}

void SuffixArray::printNode(const SANode &node) const
{
	string res;
	for(auto it = stringList[node.strIdx].begin() + node.leftIndex;
		it != stringList[node.strIdx].end(); ++it)
	{
		res += *it;
	}
	cout << "(" << res << ", index:" << node.index << ", lcp: " << node.lcp << ")" 
		 << endl;
}

void unitTests()
{
	SuffixArray sa("abracadabra");
	sa.updateVector();
	sa.print();
	sa.add("abra");
	cout << endl;
	sa.updateVector();
	sa.print();
	cout << endl;
	sa.add("cadavarzebra");
	sa.updateVector();
	sa.print();

	cout << sa.substringBinSearch(0) << endl;
	cout << sa.substringBinSearch(109) << endl;
	cout << sa.substringBinSearch(110) << endl;
	cout << sa.substringBinSearch(111) << endl;
	cout << sa.substringBinSearch(112) << endl;
	cout << sa.substringBinSearch(113) << endl;
	cout << sa.substringBinSearch(114) << endl;
	cout << sa.substringBinSearch(1) << endl;
	cout << sa.substringBinSearch(3) << endl;
	cout << sa.substringBinSearch(4) << endl;
	cout << sa.substringBinSearch(11) << endl;

	cout << endl << "SUBSTRINGS" << endl;
	sa.updateSubstringVec();
	sa.printSubstrings();
}

void solveFindStrings()
{
	int n;
	cin >> n;
	SuffixArray sa;
	for(int index = 0; index < n; ++index)
	{
		string s;
		cin >> s;
		sa.add(s);
	}
//	sa.updateSubstringVec();
	int q;
	cin >> q;
	for(int query = 0; query < q; ++query)
	{
		long long idx;
		cin >> idx;
		cout << sa.substring(idx-1) << endl;
	}
}

int main(int argc, char *argv[])
{
//	solveFindStrings();
	unitTests();
	return 0;
}
