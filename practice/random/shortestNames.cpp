#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(26)

struct Node {
	Node *arr[MAX];
	int cnt;
	Node() {
		for (int i = 0; i < MAX; i++) arr[i] = nullptr;
		cnt = 0;
	}
};	

Node *root;
void insert(string &s) {
	Node *curr = root;
	for (int i = 0; i < s.length(); i++) {
		int c = s[i] - 'a';
		if (!curr->arr[c]) curr->arr[c] = new Node();
		curr->arr[c]->cnt++;
		curr = curr->arr[c];
	}
}

void solve() {
	int n; cin >> n;
	root = new Node();
	vector<string> names(n);
	for (string &s : names) cin >> s, insert(s);

	int cnt = 0;
	for (string &s : names) {
		Node *curr = root;
		for (int i = 0; i < s.length(); i++) {
			int c = s[i] - 'a';
			if (curr->arr[c]->cnt == 1) {
				cnt++;
				break;
			}
			cnt++;
			curr = curr->arr[c];
		}
	}

	cout << cnt << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}