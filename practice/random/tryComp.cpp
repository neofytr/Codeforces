#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(26)

struct Node {
	Node *arr[MAX];
	int cntbest; string str; // best word in the current prefix subtree and its count
	int cnt; // the number of occurrences of the current prefix as a word

	Node() {
		for (int i = 0; i < MAX; i++) arr[i] = nullptr;
		cnt = cntbest = 0; str = "";
	}
};

Node *root;
void insert(string s) {
	int n = s.length();
	Node *curr = root;
	for (int i = 0; i < n; i++) {
		int c = s[i] - 'a';
		if (!curr->arr[c]) curr->arr[c] = new Node();
		curr = curr->arr[c];
	}
	int j = ++curr->cnt;

	curr = root;
	for (int i = 0; i < n; i++) {
		int c = s[i] - 'a';
		Node *nxt = curr->arr[c];
		if (nxt->cntbest < j) nxt->cntbest = j, nxt->str = s;
		else if (nxt->cntbest == j && nxt->str > s) nxt->str = s;
		curr = nxt;
	}
}

int32_t main() {
	int n; cin >> n;
	root = new Node(); string s;
	for (int i = 1; i <= n; i++)
		cin >> s, insert(s);

	int q; cin >> q;
	while (q--) {
		cin >> s;
		Node *curr = root;
		bool ok = true;
		for (int i = 0; i < s.length(); i++) {
			int c = s[i] - 'a';
			if (!curr->arr[c]) {
				cout << -1 << endl;
				ok = false;
				break;
			}
			curr = curr->arr[c];
		}
		if (ok) 
			cout << curr->str << " " << curr->cntbest << endl;
	}
	return 0;
}