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
	bool ok = false;
	for (int bit = 30; bit >= 0; bit--) {
		int c = (num >> bit) & 1;
		if (!curr->arr[c]) {
			ok = true;
			break;
		}
		curr = curr->arr[c];
	}

	if (!ok) return;

	curr = root;
	for (int bit = 30; bit >= 0; bit--) {
		int c = (num >> bit) & 1;
		if (!curr->arr[c]) curr->arr[c] = new Node();
		curr->arr[c]->cnt++;
		curr = curr->arr[c];
	}
}

void remove(int num) {
	Node *curr = root;

	for (int bit = 30; bit >= 0; bit--) {
		int c = (num >> bit) & 1;
		if (!curr->arr[c]) return;
		curr = curr->arr[c];
	}

	curr = root;
	Node *todel = nullptr;

	for (int bit = 30; bit >= 0; bit--) {
		int c = (num >> bit) & 1;

		Node *nxt = curr->arr[c];

		if (!(--nxt->cnt) && !todel) {
			todel = nxt;
			curr->arr[c] = nullptr;
		}

		curr = nxt;
	}

	delete todel;
}

int min_xor(int x) {
	Node *currnode = root; int curr = 0;
	for (int bit = 30; bit >= 0; bit--) {
		int want = ((x >> bit) & 1);
		if (!currnode->arr[want]) curr |= ((!want) << bit), currnode = currnode->arr[!want];
		else curr |= (want << bit), currnode = currnode->arr[want];
	}
	return x ^ curr;
}

int32_t main() {
	int q; cin >> q;
	root = new Node();
	while (q--) {
		int c, x;
		cin >> c >> x;
		if (!c) insert(x);
		else if (c == 1) remove(x);
		else cout << min_xor(x) << endl;
	}
	return 0;
}