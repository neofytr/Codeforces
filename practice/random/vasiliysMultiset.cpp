#include <bits/stdc++.h>
using namespace std;

#define int long long
#define BIT (int)(31)

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

void remove(int num) {
	Node *curr = root;
	for (int bit = 30; bit >= 0; bit--) {
		int c = (num >> bit) & 1;
		Node *nxt = curr->arr[c];
		if (!(--curr->arr[c]->cnt))
	}
}

int32_t main() {
	int q; cin >> q;

	return 0;
}