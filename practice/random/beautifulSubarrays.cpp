#include <bits/stdc++.h>
using namespace std;

#define int long long
#define BIT (int)(2)

struct Node {
	Node *arr[BIT]; // which bit after the current prefix is active?
	int cnt; // how many numbers have the current prefix as their prefix?

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

int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, k; cin >> n >> k;
	vector<int> arr(n + 1), p(n + 1, 0);
	for (int i = 1; i <= n; i++) cin >> arr[i], p[i] = p[i - 1] ^ arr[i];

	root = new Node(); insert(p[0]);
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		Node *curr = root;
		bool ok = true;
		for (int bit = 30; bit >= 0; bit--)
			if ((k >> bit) & 1) {
				int want = !((p[i] >> bit) & 1);
				if (!curr->arr[want]) {
					ok = false;
					break;
				}
				curr = curr->arr[want];
			} else {
				int one = !((p[i] >> bit) & 1);
				int zero = !one;

				if (curr->arr[one]) cnt += curr->arr[one]->cnt;
				if (!curr->arr[zero]) {
					ok = false;
					break;
				}
				curr = curr->arr[zero];
			}
		if (ok) cnt += curr->cnt;
		insert(p[i]);
	}

	cout << cnt << endl;
	return 0;
}