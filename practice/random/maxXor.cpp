#include <bits/stdc++.h>
using namespace std;

#define int long long
#define BIT (int)(2)

struct Node {
	Node *arr[BIT];
	bool end;

	Node() {
		for (int i = 0; i < BIT; i++) arr[i] = nullptr;
		end = false;
	}
};

Node *root;
void insert(int num) {
	Node *curr = root;
	for (int bit = 30; bit >= 0; bit--) {
		int c = (num >> bit) & 1;
		if (!curr->arr[c]) curr->arr[c] = new Node();
		curr = curr->arr[c];
	}
	curr->end = true;
}

void solve() {
	int n, m; cin >> n >> m;
	vector<int> a(n);
	for (int i = 0; i < n; i++) cin >> a[i];

	int i = 0;
	sort(a.begin(), a.end());

	vector<pair<int, int>> q(m);
	for (auto &[y, x] : q) cin >> x >> y;
	sort(q.begin(), q.end());

	root = new Node(); root->end = true;
	for (auto &[y, x] : q) {
		while (a[i] <= y) insert(a[i++]);

		Node *currnode = root; int curr = 0;
		if (!currnode->arr[0] && !currnode->arr[1]) {
			cout << -1 << " ";
			continue;
		}
		for (int bit = 30; bit >= 0; bit--) {
			int want = !((x >> bit) & 1);
			if (!currnode->arr[want]) curr |= ((!want) << bit), currnode = currnode->arr[!want];
			else curr |= (want << bit), currnode = currnode->arr[want];
		}
		cout << (x ^ curr) << " ";
	}
	cout << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}