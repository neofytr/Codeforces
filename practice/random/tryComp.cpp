#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(26)

struct Node {
	Node *arr[MAX];
	bool end;
	int cnt;

	Node() {
		for (int i = 0; i < MAX; i++) arr[i] = nullptr;
		end = false; cnt = 0;
	}
};

Node *root;
void insert(string &s) {
	Node *curr = root;
	curr->cnt++;
	for (int i = 0; i < s.length(); i++) {
		int c = s[i] - 'a';
		if (!curr->arr[c]) curr->arr[c] = new Node();
		curr = curr->arr[c];
	}
	curr->end = true; curr->cnt++;
}

string str; int res = -1;
void dfs(Node *node, string &build) {
	if (node->end) 
		if (node->cnt > res) str = build, res = node->cnt;
		else if (node->cnt == res && build < str) str = build;

	for (int i = 0; i < 26; i++) 
		if (node->arr[i]) {
			build.push_back((char)(i + 'a'));
			dfs(node->arr[i], build);
			build.pop_back();
		}
}

int32_t main() {
	int n; cin >> n;
	string s;
	root = new Node();
	for (int i = 1; i <= n; i++) cin >> s, insert(s);

	int q; cin >> q;
	while(q--) {
		cin >> s;

		Node *curr = root; res = 0, str = "";
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

		if (ok) {
			dfs(curr, s);
			cout << str << " " << res << endl;
		}
	}

	return 0;
}