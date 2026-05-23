#include <bits/stdc++.h>
using namespace std;

#define int long long
#define BIT (int)(2)

struct Node {
	Node *nxt[BIT];
	bool exist;
	Node() {
		for (int i = 0; i < BIT; i++) nxt[i] = nullptr;
		exist = false;
	}
};

Node *root;
void insert(int num) {
	Node *curr = root;
	for (int bit = 20; bit >= 0; bit--) {
		int c = (num >> bit) & 1;
		if (!curr->nxt[c]) curr->nxt[c] = new Node();
		curr = curr->nxt[c];
	}
}

bool dfs(Node *node, int bit) {
	if (bit == -1)
		return node->exist = false;

	node->exist = (!node->nxt[0]) || (!node->nxt[1]);

	if (node->nxt[0])
		node->exist |= dfs(node->nxt[0], bit - 1);

	if (node->nxt[1])
		node->exist |= dfs(node->nxt[1], bit - 1);

	return node->exist;
}

int32_t main() {
	int n, m; cin >> n >> m;
	root = new Node();
	vector<int> a(n + 1);
	for (int i = 1; i <= n; i++) cin >> a[i], insert(a[i]);

	dfs(root, 20);
	int p = 0;
	for (int i = 1; i <= m; i++) {
		int x;
		cin >> x;
		p ^= x;
		int curr = 0; Node *currnode = root;
		int res = LLONG_MAX;
		for (int bit = 20; bit >= 0; bit--) {
			int cpy = curr;
			if (!currnode->nxt[0]) {
				int tmp = 0;
				for (int b = 20; b >= bit; b--)
					tmp |= ((((cpy >> b) & 1) ^ ((p >> b) & 1)) << b);
				res = min(res, tmp);
			}

			if (!currnode->nxt[1]) {
				int tmp = 0;
				cpy |= (1 << bit);
				for (int b = 20; b >= bit; b--)
					tmp |= ((((cpy >> b) & 1) ^ ((p >> b) & 1)) << b);
				res = min(res, tmp);
			}

			if (currnode->nxt[1] && currnode->nxt[0]) {
				int take = (p >> bit) & 1;
				if (currnode->nxt[take]->exist) {
					currnode = currnode->nxt[take];
					curr |= (take << bit);
				} else {
					currnode = currnode->nxt[!take];
					curr |= (!take << bit);
				}
			} else if (currnode->nxt[0]) currnode = currnode->nxt[0];
			else currnode = currnode->nxt[1], curr |= (1 << bit);
		}

		cout << res << endl;
	}
	return 0;
}