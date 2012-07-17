#include <cstdio>

using namespace std;

template<typename T>
struct Node {
	Node(const T& _data) : left(NULL), right(NULL), parent(NULL), 
						   data(_data), size(1) {}
	Node<T> *left, *right, *parent;
	T data;
	int size;
	int height;
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

	void remove(const T &data) {
		if(root != NULL) {
			Node<T> *todelete = findNodeWithValue(root, data);
			remove(todelete);
		}
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
	}

	Node<T> *findNodeWithValue

private:
	Node<T> *root;
};


int main(int argc, char *argv[])
{
	return 0;
}
