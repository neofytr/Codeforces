#include <bits/stdc++.h>
using namespace std;

#define int long long
#define NUM (int)(26)

struct Node {
	Node *arr[NUM];
	bool end;

	Node() {
		this->end = false;
		for (int i = 0; i < NUM; i++) this->arr[i] = nullptr;
	}
};

// accepts only lowercase latin characters
// node->arr[c] is null iff the character c doesn't exist at the node
class Trie {
private:
	Node *root;

public:
	Trie() {
		root = new Node();
	}

	void insert(const string &s) {
		int n = s.length();
		Node *curr = root;

		for (int i = 0; i < n; i++) {
			int c = s[i] - 'a';
			if (!curr->arr[c]) curr->arr[c] = new Node();
			curr = curr->arr[c];
		}
		curr->end = true;
	}

	bool contains(const string &s) const {
		int n = s.length();
		const Node *curr = root;

		for (int i = 0; i < n; i++) {
			int c = s[i] - 'a';
			if (!curr->arr[c]) return false;
			curr = curr->arr[c];
		}
		return curr->end;
	}

	bool starts_with(const string &s) const {
		int n = s.length();
		Node *curr = root;

		for (int i = 0; i < n; i++) {
			int c = s[i] - 'a';
			if (!curr->arr[c]) return false;
			curr = curr->arr[c];
		}
		return true;
	}
};

int32_t main() {
	Trie tree;

	tree.insert("hello");
	tree.insert("hell");
	tree.insert("old");

	cout << tree.starts_with("he") << endl;
	return 0;
}