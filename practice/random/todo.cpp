#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(26)

struct Node {
	Node *arr[MAX]; // the characters that can extend the current prefix
	int cnt; // the number of words that have the current prefix

	Node() {
		for (int i = 0; i < MAX; i++) arr[i] = nullptr;
		cnt = 0;
	}
};

Node *root; // the empty prefix
void insert(string &s) {
	Node *curr = root; // the current prefix is ""
	curr->cnt++; // the empty prefix is a prefix of all strings
	for (int i = 0; i < s.length(); i++) {
		int c = s[i] - 'a';
		if (!curr->arr[c]) curr->arr[c] = new Node();
		curr->arr[c]->cnt++;
		curr = curr->arr[c];
	}
}

int32_t main() {
	int n, q; cin >> n >> q;
	root = new Node();

	string s;
	for (int i = 1; i <= n; i++) cin >> s, insert(s);
	for (int i = 1; i <= q; i++) {
		cin >> s;

		Node *curr = root;
		bool ok = true;
		for (int i = 0; i < s.length(); i++) {
			int c = s[i] - 'a';
			if (!curr->arr[c]) {
				ok = false;
				break;
			}
			curr = curr->arr[c];
		}
		if (ok) cout << curr->cnt << endl;
		else cout << 0 << endl;
	}
	return 0;
}