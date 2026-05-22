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
	vector<int> a(n + 1);
	for (int i = 1; i <= n; i++) cin >> a[i];

	root = new Node(); root->end = true;
	for (int i = 1; i <= n; i++) insert(a[i]);

	int x, y;
	while (m--) {
		cin >> x >> y;

		Node *currnode = root;
		int curr = 0;
		bool canchoseany = false;
		bool bad = false;
		for (int bit = 30; bit >= 0; bit--) {
			int want = !((x >> bit) & 1);
			int c = -1;
			if (!((y >> bit) & 1)) {
				if (want && canchoseany) {
					if (!currnode->arr[want]) curr |= ((!want) << bit), c = !want;
					else curr |= (want << bit), c = want;
				} else if (!currnode->arr[0]) {
						cout << -1 << " ";
						bad = true;
						break;
					} else c = 0;
			} else {
				if (!currnode->arr[want]) curr |= ((!want) << bit), c = !want;
				else curr |= (want << bit), c = want;

				if (!want && currnode->arr[want]) canchoseany = true;
			}
			currnode = currnode->arr[c];
		}
		if (!bad)
			cout << (x ^ curr) << " ";
	}
	cout << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}