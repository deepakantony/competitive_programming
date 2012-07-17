#include <cstdio>

using namespace std;

template<typename T>
struct Node {
	Node(const T& _data) : left(NULL), right(NULL), parent(NULL), 
						   data(_data), size(1), balFactor(0), count(1) {}
	void update() {
		// update size
		size = count;
		if(right) size += right->size;
		if(left) size += left->size;

		// update balfactor
		
	}
	Node<T> *left, *right, *parent;
	T data;
	int count;
	int size;
	int balFactor;
};

template<typename T>
class BST {
public:
	BST() : root(NULL) {}

	int size() { root == NULL ? 0 : root.size(); }

	void add(const T &data) {
		if(root == NULL) root = new Node(data);
		else add(root, data);
	}

	bool remove(const T &data) {
		if(root != NULL) {
			Node<T> *todelete = findNodeWithValue(root, data);
			
			if(todelete) {remove(todelete); return true; }
		}
		return false;
	}

	float median() {
		assert(root != NULL);
		int mid = size/2;
		if(root->size % 2 == 0)
			return (float)(median(root, mid) + median(root, mid+1))/2.f;
		else return median(root, mid);
	}
private:
	void add(Node<T> *cur, const T &data) {
		if(cur->data == data) { cur->size++; cur->count++; return; }

		if(cur->data < data) // data is greater
			if(cur->right == NULL) cur->right = new Node(data); 
			else add(cur->right, data);
		else if(cur->left == NULL) cur->left = new Node(data);
		else add(cur->left, data);

		
	}

	Node<T> *findNodeWithValue(Node<T> *cur, const T &data) {
		while(cur && cur->data != data) 
			cur = cur->data > data ? cur->left : cur->right;
		return cur;
	}

	

private:
	Node<T> *root;
};


int main(int argc, char *argv[])
{
	return 0;
}
