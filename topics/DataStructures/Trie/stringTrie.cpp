#include <bits/stdc++.h>
using namespace std;

#define int long long
#define NUM (int)(26)

struct Node {
	Node *arr[NUM];
	bool end;

	Node (bool end) {
		this->end = end;
		for (int i = 0; i < NUM; i++) arr[i] = nullptr;
	}
};

// accepts only lowercase latin characters
class Trie {
private:
	Node *root;

	void _insert(Node *node, const string &s, int i) {
		int n = s.length();
		if (i >= n) {
			node->end = true;
			return;
		}

		int c = s[i] - 'a';
		if (!node->arr[c]) node->arr[c] = new Node(false);
		_insert(node->arr[c], s, i + 1);
	}

	bool _contains(Node *node, const string &s, int i) const {
		int n = s.length();
		if (!node) return false;
		if (i >= n) return node->end;

		int c = s[i] - 'a';
		return _contains(node->arr[c], s, i + 1);
	}

	bool _starts_with(Node *node, const string &s, int i) const {
		int n = s.length();
		if (!node) return false;
		if (i >= n) return true;
		int c = s[i] - 'a';
		return _starts_with(node->arr[c], s, 0); 
	}

public:
	Trie() {
		this->root = new Node(false);
	}

	void insert(const string &s) {
		_insert(root, s, 0);
	}

	bool contains(const string &s) const {
		return _contains(root, s, 0);
	}

	bool starts_with(const string &s) const {
		return _starts_with(root, s, 0);
	}
};

int32_t main() {
	Trie tree;

	tree.insert("hello");
	tree.insert("hell");
	tree.insert("old");

	cout << tree.contains("hello") << endl;
	cout << tree.starts_with("he") << endl;
	cout << tree.contains("lets") << endl;
	cout << tree.starts_with("x") << endl;
	return 0;
}