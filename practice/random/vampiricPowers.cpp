#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(1e5)
#define NUM (int)(2)

struct Node {
	Node *arr[NUM];
	bool end;

	Node() {
		for (int i = 0; i < NUM; i++) arr[i] = nullptr;
		end = false;
	}
};

class Trie {
private:
	Node *root;

public:
	Trie() {
		root = new Node();
	}

	void insert(const int num) {
		Node *curr = root;
		for (int bit = 7; bit >= 0; bit--) {
			int c = (num & (1ll << bit)) ? 1 : 0;
			if (!curr->arr[c]) curr->arr[c] = new Node();
			curr = curr->arr[c];
		}
		curr->end = true;
	}

	bool contains(const int num) const {
		Node *curr = root;
		for (int bit = 7; bit >= 0; bit--) {
			int c = (num & (1ll << bit)) ? 1 : 0;
			if (!curr->arr[c]) return false;
			curr = curr->arr[c];
		}
		return curr->end;
	}

	bool starts_with(const int num, int len) const {
		Node *curr = root;
		for (int bit = 7; bit >= 8 - len; bit--) {
			int c = (num & (1ll << bit)) ? 1 : 0;
			if (!curr->arr[c]) return false;
			curr = curr->arr[c];
		}
		return true;
	}
};


void solve() {
	int n; cin >> n;
	vector<int> a(n + 1), p(n + 1, 0);
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) p[i] = p[i - 1] ^ a[i];

	Trie tree;
	tree.insert(p[0]);

	int maxi = LLONG_MIN;
	for (int i = 1; i <= n; i++) {
		int want = 0xFFFF & ~p[i];
		int curr = 0;

		for (int bit = 7; bit >= 0; bit--) {
			int c = want & (1ll << bit);
			curr |= c;
			if (!tree.starts_with(curr, 8 - bit)) 
				if (!c) curr |= (1ll << bit);
				else curr &= ~(1ll << bit);
		}
		maxi = max(maxi, p[i] ^ curr);
		tree.insert(p[i]);
	}

	cout << maxi << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}