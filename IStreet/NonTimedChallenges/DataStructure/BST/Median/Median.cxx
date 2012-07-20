#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <vector>
#include <ctime>

using namespace std;

#define REP(i, n) for(int i = 0; i < (n); ++i)

template<typename T>
struct Node {
	Node(const T& _data, Node<T> *p) : left(NULL), right(NULL), parent(p), 
									   data(_data), count(1), size(1),
									   height(0) {}

	void updateSizeAndHeight() {
		// update size
		size = count;
		if(right) size += right->size;
		if(left) size += left->size;

		// update height
		height = 0;
		if(right) height = max(height, right->height+1);
		if(left) height = max(height, left->height+1);
	}
	Node<T> *left, *right, *parent;
	T data;
	int count;
	int size;
	int height;
};

template<typename T>
class BST {
public:
	BST() : root(NULL) {}

	int size() { return root == NULL ? 0 : root->size; }

	void add(const T &data) {
		if(root == NULL) root = new Node<T>(data, NULL); 
		else add(root, data);
		assert(root != NULL);
	}

	bool remove(const T &data) {
		if(root != NULL) {
			Node<T> *todelete = findNodeWithValue(root, data);
			
			if(todelete) {remove(todelete); return true; }
		}
		return false;
	}

	T getElementAt(int index) {
		assert(root != NULL);
		assert(index > 0 && index <= size());
		return getElementAt(root, index);
	}

	void inorderPrint() {
		inorder(root);
		printf("\n");
	}
	void inorder(Node<T> *cur){
		if(cur!=NULL) {
			printf(" [ ");
			inorder(cur->left);
			if(cur->left) printf("<-");
			printf(" %d ", cur->data);
			if(cur->right) printf("->");
			inorder(cur->right);
			printf(" ] ");
		}
	}
		
private:
	void add(Node<T> *cur, const T &data) {
		assert(cur != NULL);
		if(cur->data == data) { cur->size++; cur->count++; return; }

		if(cur->data < data) { // data is greater
			if(cur->right == NULL) cur->right = new Node<T>(data, cur); 
			else add(cur->right, data);
		}
		else if(cur->left == NULL) cur->left = new Node<T>(data, cur);
		else add(cur->left, data);

		updateTillRoot(cur);
	}

	void remove(Node<T> *toDelete) {
		if(toDelete == NULL) return;
		if(toDelete->count > 1) { 
			toDelete->count--; updateTillRoot(toDelete); 
			return; 
		}

		assert(toDelete->count == 1);

		// the toDelete node does not have any child
		if(toDelete->left == NULL && toDelete->right == NULL) {
			if(toDelete == root) root = NULL;
			else if(toDelete->parent->left == toDelete)
				toDelete->parent->left = NULL;
			else toDelete->parent->right = NULL;
		}

		// the toDelete node does not have left child
		else if(toDelete->left == NULL) {
			if(toDelete == root) {
				root = toDelete->right;
				root->parent = NULL;
			}
			else if(toDelete == toDelete->parent->left) {
				toDelete->parent->left = toDelete->right;
				toDelete->right->parent = toDelete->parent;
			}
			else {
				toDelete->parent->right = toDelete->right;
				toDelete->right->parent = toDelete->parent;
			}
		}

		// the toDelete node does not have right child
		else if(toDelete->right == NULL) {
			if(toDelete == root) {
				root = toDelete->left;
				root->parent = NULL;
			}
			else if(toDelete == toDelete->parent->left) {
				toDelete->parent->left = toDelete->left;
				toDelete->left->parent = toDelete->parent;
			}
			else {
				toDelete->parent->right = toDelete->left;
				toDelete->left->parent = toDelete->parent;
			}
		}
		else {

			// both subtrees exist;
			// find the largest element in the left node and exchange and 
			// delete the largest element node
			Node<T> *largestInLeftNode = largest(toDelete->left);
			
			if(largestInLeftNode == toDelete->left) {
				toDelete->left = largestInLeftNode->left;
				if(largestInLeftNode->left)
					largestInLeftNode->left->parent = toDelete;
			}
			else {
				largestInLeftNode->parent->right = largestInLeftNode->left;
				if(largestInLeftNode->left)
					largestInLeftNode->left->parent = toDelete;
			}
			swap(largestInLeftNode->data, toDelete->data);
			toDelete = largestInLeftNode;
		}

		updateTillRoot(toDelete->parent);
		delete toDelete;
	}

	Node<T> *findNodeWithValue(Node<T> *cur, const T &data) {
		while(cur && cur->data != data) 
			cur = cur->data > data ? cur->left : cur->right;
		return cur;
	}

	T getElementAt(Node<T> *cur, int index) {
		assert(cur != NULL);
		assert(index > 0);
		int curLow = 0;
		if(cur->left) curLow += cur->left->size;
		if(index > curLow && index <= curLow+cur->count) return cur->data;

		if(index <= curLow) return getElementAt(cur->left, index);
		return getElementAt(cur->right, index - curLow - cur->count);
	}

	Node<T> *largest(Node<T> *cur) {
		if(cur->right == NULL) return cur;
		return largest(cur->right);
	}

	int heightDiff(Node<T> *node1, Node<T> *node2) {
		if(node1 && node2) return node1->height - node2->height;
		if(node1 == NULL && node2 == NULL) return 0;
		if(node2 == NULL) return node1->height;
		return -node2->height;
	}

	void rotateLeft(Node<T> *p) {
		//fprintf(stderr, "Rotate Left\n");
		assert(p!=NULL);
		if(p->right == NULL) return;

		Node<T> *oldright = p->right;
		p->right = oldright->left;
		if(p->right) p->right->parent = p;
		oldright->left = p;
		oldright->parent = p->parent;
		p->parent = oldright;

		if(p != root) {
			if(oldright->parent->left == p)
				oldright->parent->left = oldright;
			else oldright->parent->right = oldright;
		}
		else { root = oldright; root->parent = NULL; }
		p->updateSizeAndHeight();
		oldright->updateSizeAndHeight();
	}

	void rotateRight(Node<T> *p) {
		//fprintf(stderr, "Rotate Right\n");
		assert(p!=NULL);
		if(p->left == NULL) return;

		Node<T> *oldleft = p->left;
		p->left = oldleft->right;
		if(p->left) p->left->parent = p;
		oldleft->right = p;
		oldleft->parent = p->parent;
		p->parent = oldleft;

		if(p != root) {
			if(oldleft->parent->left == p)
				oldleft->parent->left = oldleft;
			else oldleft->parent->right = oldleft;
		}
		else { root = oldleft; root->parent = NULL; }
		p->updateSizeAndHeight();
		oldleft->updateSizeAndHeight();
	}

	void balance(Node<T> *cur) {
		cur->updateSizeAndHeight();
		int balanceFactor = heightDiff(cur->left, cur->right);

		//fprintf(stderr,"BALANCEFACTOR: %d", balanceFactor);

		assert(balanceFactor > -3 && balanceFactor < 3);
		if(balanceFactor == 2) { // left subtree heavy
			int balanceFactorL = heightDiff(cur->left->left, cur->left->right);
			if(balanceFactorL < 0) // right heavy
				rotateLeft(cur->left);
			rotateRight(cur);
		}
		else if(balanceFactor == -2) {
			int balanceFactorR = heightDiff(cur->right->left, cur->right->left);
			if(balanceFactorR > 0) // left heavy
				rotateRight(cur->right);
			rotateLeft(cur);
		}

		cur->updateSizeAndHeight();
	}

	void updateTillRoot(Node<T> *cur) {
		if(cur != NULL) {
			balance(cur);
			updateTillRoot(cur->parent);
		}
	}

private:
	Node<T> *root;
	friend void unittests();
};


void unittests() {
	//int testlist[] = {1,1,1,2,2,3,4,5,6,7,8,9,10,10,11};
	//int testlist[] = {2, 4, 9, 8, 6, 7};
	srand(time(NULL));
	vector<int> testlist;
	REP(i, 1000000){
		testlist.push_back(rand()%10000);
	}
	int size = testlist.size(); 
	//int size = sizeof(testlist)/sizeof(int);
	BST<int> tree;	
	REP(i, size) {
		//tree.inorderPrint();
		tree.add(testlist[i]);
		//if(tree.root)
		//fprintf(stderr,	"%d %d\n",tree.root->height, tree.root->size);

		assert(tree.size() == i+1);
		//printf("%d %d %d %d\n", i, testlist[i], tree.size(), tree.getElementAt(i+1));
		//assert(tree.getElementAt(i+1) == testlist[i]);
	}
	//fprintf(stderr, "Done creating the tree\n");
	sort(testlist.begin(), testlist.end());
	//sort(testlist, testlist+size);
	REP(i, size) {
		assert(tree.getElementAt(i+1) == testlist[i]);
	}

	REP(i, size) {
		assert(tree.remove(i+10001) == false);

		assert(tree.getElementAt(size-i) == testlist[size-i-1]);
		assert(tree.remove(testlist[size-i-1]));
		assert(tree.size() == (size-i-1));
		if(i != size-1)
			assert(tree.getElementAt(size-i-1) == testlist[size-i-2]);

	}

	
}

void solveMedian() {
	int N;
	char op;
	int num;
	scanf(" %d", &N);
	BST<int> tree;
	bool printMedian;
	while(N--) {
		scanf(" %c %d", &op, &num);
		if(op == 'a') {
			tree.add(num);
			printMedian = true;
		}
		else printMedian = tree.remove(num);

		if(tree.size() == 0) printMedian = false;
		if(printMedian) {
			if(tree.size() % 2 == 0) {
				unsigned int sum = tree.getElementAt(tree.size()/2) + 
					tree.getElementAt(tree.size()/2+1);
				if(sum%2==0) printf("%u\n", sum/2);
				else printf("%u.5\n", sum/2);
			}
			else printf("%d\n", tree.getElementAt((tree.size()/2)+1));
		}
		else printf("Wrong!\n");
	}
}

int main(int argc, char *argv[])
{
	//unittests();
	solveMedian();
	return 0;
}
