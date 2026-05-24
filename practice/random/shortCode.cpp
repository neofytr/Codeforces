#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(26)

struct Node {
	Node *nxt[MAX];
	vector<vector<int>> dp;
	bool end; int len; int cnt; int dpt;
	Node() {
		for (int i = 0; i < MAX; i++) nxt[i] = nullptr;
		dp.resize(MAX);
		for (int i = 0; i < MAX; i++)
			dp[i].resize(2), dp[i][0] = dp[i][1] = -1;
		end = false; len = cnt = dpt = 0;
	}
};

Node *root;
void insert(string &s) {
	Node *curr = root; 
	for (int i = 0; i < s.length(); i++) {
		int c = s[i] - 'a';
		if (!curr->nxt[c]) curr->nxt[c] = new Node();
		curr->nxt[c]->len = max(curr->nxt[c]->len, (int)s.length() - i);
		curr->nxt[c]->cnt++;
		curr->nxt[c]->dpt = i + 1;
		curr = curr->nxt[c];
	}
	curr->end = true;
}

int cnt = 0;
void dfs(Node *node, int done) {
	
}

int32_t main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n; cin >> n;
	string s;
	root = new Node(); 
	for (int i = 1; i <= n; i++) cin >> s, insert(s);
	for (int c = 0; c < MAX; c++)
		if (root->nxt[c]) dfs(root->nxt[c], 0);
	cout << cnt << endl;
	return 0;
} 