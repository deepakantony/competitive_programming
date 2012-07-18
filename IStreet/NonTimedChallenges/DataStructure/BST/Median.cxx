#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cassert>

using namespace std;

template<typename T>
struct Node {
	Node(const T& _data, Node<T> *p) : left(NULL), right(NULL), parent(p), 
						   data(_data), size(1), count(1), height(0) {}
	void updateSizeAndHeight() {
		// update size
		size = count;
		if(right) size += right->size;
		if(left) size += left->size;

		// update balfactor
		height = 0;
		if(right) height = max(height, right->height);
		if(left) height = max(height, left->height);
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

	int size() { root == NULL ? 0 : root.size(); }

	void add(const T &data) {
		if(root == NULL) root = new Node<T>(data, NULL);
		else add(root, data);
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
		return getElementAt(root, index);
	}
private:
	void add(Node<T> *cur, const T &data) {
		if(cur->data == data) { cur->size++; cur->count++; return; }

		if(cur->data < data) // data is greater
			if(cur->right == NULL) cur->right = new Node<T>(data, cur); 
			else add(cur->right, data);
		else if(cur->left == NULL) cur->left = new Node<T>(data, cur);
		else add(cur->left, data);

		int balanceFactor = heightDiff(cur->left, cur->right);
		assert(balanceFactor < 3 && balanceFactor > -3);
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

	void remove(Node<T> *toDelete) {
		if(toDelete == NULL) return;
		if(toDelete->count > 1) { 
			toDelete->count--; updateSizeAndHeight(toDelete); 
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
			// delete
			Node<T> *largestInLeftNode = largest(toDelete->left);
			
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
		largest(cur->right);
	}

	int heightDiff(Node<T> *node1, Node<T> *node2) {
		if(node1 && node2) return node1->height - node2->height;
		if(node1 == NULL && node2 == NULL) return 0;
		if(node2 == NULL) return node1->height;
		return -node2->height;
	}

	void rotateLeft(Node<T> *p) {
		assert(p!=NULL);
		if(p->right == NULL) return;

		Node<T> *oldright = p->right;
		p->right = p->right->left;
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
	}

	void rotateRight(Node<T> *p) {
		assert(p!=NULL);
		if(p->left == NULL) return;

		Node<T> *oldleft = p->left;
		p->left = p->left->right;
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
	}

private:
	Node<T> *root;
};


int main(int argc, char *argv[])
{
	BST<int> avltree;
	avltree.median(10);
	return 0;
}
