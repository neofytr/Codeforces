#include <bits/stdc++.h>
using namespace std;

#define int long long
#define BIT (int)(2)

struct Node {
	Node *nxt[BIT];
	int pos;
	Node() {
		for (int i = 0; i < BIT; i++) nxt[i] = nullptr;
		pos = 0;
	}
};

Node *root;
void insert(int num, int i) {
	Node *curr = root;
	for (int bit = 30; bit >= 0; bit--) {
		int c = (num >> bit) & 1;
		if (!curr->nxt[c]) curr->nxt[c] = new Node();
		curr->nxt[c]->pos = max(curr->nxt[c]->pos, i);
		curr = curr->nxt[c];
	}
}

void solve() {
	int n, k; cin >> n >> k;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; i++) cin >> a[i];

	int res = LLONG_MAX;
	root = new Node();
	for (int i = 1; i <= n; i++) {
		insert(a[i], i);

		bool ok = true;
		Node *currnode = root;
		for (int bit = 30; bit >= 0; bit--)
			if ((k >> bit) & 1) {
				int want = !((a[i] >> bit) & 1);
				if (!currnode->nxt[want]) {
					ok = false;
					break;
				}
				currnode = currnode->nxt[want];
			} else {
				int zero = (a[i] >> bit) & 1;
				int one = !zero;

				if (currnode->nxt[one]) res = min(res, i - currnode->nxt[one]->pos + 1);
				if (!currnode->nxt[zero]) {
					ok = false;
					break;
				}
				currnode = currnode->nxt[zero];
			}
		if (ok) res = min(res, i - currnode->pos + 1);
	}

	cout << (res == LLONG_MAX ? -1 : res) << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}