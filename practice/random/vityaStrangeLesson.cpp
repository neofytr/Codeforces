#include <bits/stdc++.h>
using namespace std;

#define int long long
#define BIT (int)(2)

struct Node {
	Node *nxt[BIT];
	Node() {
		for (int i = 0; i < BIT; i++) nxt[i] = nullptr;
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

int p;
int dfs(Node *currnode, int bit, int curr) {
	if (bit < 0) return 1e18;
	int res = 1e18;
	if (!currnode->nxt[0]) {
		int tmp = 0;
		for (int b = 20; b >= bit; b--)
			tmp |= ((((curr >> b) & 1) ^ ((p >> b) & 1)) << b);
		res = min(res, tmp);
	}
	if (!currnode->nxt[1]) {
		int cpy = curr | (1 << bit);
		int tmp = 0;
		for (int b = 20; b >= bit; b--)
			tmp |= ((((cpy >> b) & 1) ^ ((p >> b) & 1)) << b);
		res = min(res, tmp);
	}
	if (currnode->nxt[0])
		res = min(res, dfs(currnode->nxt[0], bit - 1, curr));
	if (currnode->nxt[1])
		res = min(res, dfs(currnode->nxt[1], bit - 1, curr | (1 << bit)));
	return res;
}

int32_t main() {
	int n, m;
	cin >> n >> m;

	root = new Node();
	for (int i = 1; i <= n; i++) {
		int x;
		cin >> x;
		insert(x);
	}

	p = 0;
	while (m--) {
		ios_base::sync_with_stdio(false);
	cin.tie(NULL);
		int x;
		cin >> x;
		p ^= x;
		cout << dfs(root, 20, 0) << endl;
	}

	return 0;
}