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
}

void _insert(Node *node, int num, int bit) {
	if (bit == 31) {
		node->cnt = 1;
	}
	int c = (num >> bit) & 1;
	if (!node->arr[c]) node->arr[c] = new Node();
}

void insert(int num) {
	_insert(root, num, 30);
}

void solve() {
	int n, k; cin >> n >> k;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; i++) cin >> a[i];


}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}