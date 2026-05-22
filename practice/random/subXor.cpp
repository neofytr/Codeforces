#include <bits/stdc++.h>
using namespace std;

#define int long long
#define BIT (int)(2)

struct Node {
	Node *arr[BIT];
	int cnt;

	Node() {
		for (int i = 0; i < BIT; i++) arr[i] = nullptr;
		cnt = 0;
	}
};

Node *root;

void insert(int num) {
	Node *curr = root;
	for (int bit = 30; bit >= 0; bit--) {
		int c = (num >> bit) & 1;
		if (!curr->arr[c]) curr->arr[c] = new Node();
		curr->arr[c]->cnt++;
		curr = curr->arr[c];
	}
}

void solve() {
	int n, k; cin >> n >> k;
	vector<int> a(n + 1), p(n + 1, 0);
	for (int i = 1; i <= n; i++) cin >> a[i], p[i] = p[i - 1] ^ a[i];

	root = new Node(); root->cnt = 1;
	insert(p[0]);

	int cnt = 0; k--;
	for (int i = 1; i <= n; i++) {
		Node *curr = root; 
		bool ok = true;
		for (int bit = 30; bit >= 0; bit--) {
			if (!((k >> bit) & 1)) {
				int want = (p[i] >> bit) & 1;
				if (!curr->arr[want]) {
					ok = false;
					break;
				}
				curr = curr->arr[want];
			} else {
				int one = !((p[i] >> bit) & 1);
				int zero = (p[i] >> bit) & 1;

				if (curr->arr[zero]) 
					cnt += curr->arr[zero]->cnt;
				if (!curr->arr[one]) {
					ok = false;
					break;
				}

				curr = curr->arr[one];
			}
		}
		if (ok) cnt += curr->cnt;
		insert(p[i]);
	}

	cout << cnt << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}