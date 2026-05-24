#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(26)

struct Node {
	Node *nxt[MAX];
	bool end; int len;
	Node() {
		for (int i = 0; i < MAX; i++) nxt[i] = nullptr;
		end = false; len = 0;
	}
};

Node *root;
void insert(string &s) {
	Node *curr = root;
	for (int i = 0; i < s.length(); i++) {
		int c = s[i] - 'a';
		if (!curr->nxt[c]) curr->nxt[c] = new Node();
		curr->nxt[c]->len = max(curr->nxt[c]->len, (int)s.length() - i - 1);
		curr = curr->nxt[c];
	}
	curr->end = true;
}

vector<char> ops;
void dfs(Node *node) {
	if (node->end) ops.push_back('P');
	vector<pair<int, pair<int, Node *>>> v;
	for (int i = 0; i < MAX; i++)
		if (node->nxt[i]) v.push_back({node->nxt[i]->len, {i, node->nxt[i]}});

	sort(v.begin(), v.end());
	for (auto &[l, p] : v) {
		auto &[i, curr] = p;
		ops.push_back(i + 'a');
		dfs(curr);
		ops.push_back('-');
	}
}

int32_t main() {
	string s; root = new Node();
	int n; cin >> n;
	for (int i = 1; i <= n; i++) 
		cin >> s, insert(s);

	dfs(root);
	while (*ops.rbegin() == '-')
		ops.pop_back();
	cout << ops.size() << endl;
	for (char c : ops)
		cout << c << endl;
	return 0;
}