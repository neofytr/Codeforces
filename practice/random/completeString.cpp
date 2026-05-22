#include <bits/stdc++.h>
using namespace std;

#define int long long
#define NUM (int)(26)

struct Node {
	Node *arr[NUM];
	bool end;

	Node() {
		for (int i = 0; i < NUM; i++) arr[i] = nullptr;
		end = false;
	}
};

Node *root;
void insert(const string &s) {
	int n = s.length();
	Node *curr = root;
	for (int i = 0; i < n; i++) {
		int c = s[i] - 'a';
		if (!curr->arr[c]) curr->arr[c] = new Node();
		curr = curr->arr[c];
	}
	curr->end = true;
}

string res;
void dfs(Node *node, string s) {
	for (int i = 0; i < 26; i++)
		if (node->arr[i] && node->arr[i]->end) {
			s.push_back((char)(i + 'a'));
			dfs(node->arr[i], s);
			s.pop_back();
		}

	if (res.length() < s.length()) res = s;
	if (res.length() == s.length() && res > s) s = res;
}

void solve() {
	root = new Node(); root->end = true; res = "";
	int n; cin >> n;
	string s;
	for (int i = 1; i <= n; i++) 
		cin >> s, insert(s);

	dfs(root, "");
	if (res == "") cout << "None" << endl;
	else cout << res << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}