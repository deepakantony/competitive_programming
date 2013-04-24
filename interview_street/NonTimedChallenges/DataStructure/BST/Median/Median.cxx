// the solution is simple.
// Keep two sets and balance them to be equal and then display the middle of 
// the two.

#include <cstdio>
#include <set>
#include <cassert>

using namespace std;

typedef long long LL;
typedef multiset<LL> MI;
typedef MI::iterator MI_ITER;

class MedianSet {
public:
	MedianSet() : set1(), set2() {}
	void add(LL data) {
		if(set1.empty()) set1.insert(data);
		else if(*(--set1.end()) >= data)
			set1.insert(data);
		else set2.insert(data);
		balance();
	}

	bool remove(LL data) {
		MI_ITER it = set1.find(data);
		if(it != set1.end())
			set1.erase(it);
		else if( (it = set2.find(data)) != set2.end())
			set2.erase(it);
		else return false;
		balance();
		return true;
	}

	void printMedian() {
		if(set1.size() == 0) printf("Wrong!\n");
		else {
			int totalSize = set1.size() + set2.size();
			if(totalSize%2 == 1) // odd
				printf("%lld\n", *(--set1.end()));
			else {
				assert(set1.size() == set2.size());
				assert(*(--set1.end()) <= *(set2.begin()));
				LL out = (*(--set1.end()) + *(set2.begin()));
				if(out % 2 == 0)
					printf("%lld\n", out/2);
				else printf("%.1f\n", out/2.);
			}
		}
	}
private:
	void balance() {
		while(set1.size() > (set2.size()+1)) {
			int tempdata = *(--set1.end());
			set1.erase(--set1.end());
			set2.insert(tempdata);
		}
		while(set2.size() > set1.size()) {
			int tempdata = *(set2.begin());
			set2.erase(set2.begin());
			set1.insert(tempdata);
		}
	}

	MI set1, set2;
};

int main(int argc, char *argv[])
{
	int N; scanf(" %d", &N);
	char op; LL data;
	MedianSet tree;
	while(N--) {
		scanf(" %c %lld", &op, &data);
		switch(op) {
		case 'a': 
			tree.add(data);
			tree.printMedian();
			break;
		case 'r': 
			if(tree.remove(data)) tree.printMedian();
			else printf("Wrong!\n");
			break;
		}
	}

	return 0;
}
