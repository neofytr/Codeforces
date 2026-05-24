#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(26)

struct Node {
	Node *nxt[MAX];
	bool end;
	Node() {
		for (int i = 0; i < MAX; i++) nxt[i] = nullptr;
		end = false; 
	}
};

Node *root;
void insert(string &s) {
	Node *curr = root;
	for (int i = 0; i < s.length(); i++) {
		int c = s[i] - 'a';
		if (!curr->nxt[c]) 
			curr->nxt[c] = new Node();
		curr = curr->nxt[c];
	}
	curr->end = true;
}

int cnt = 0;
// returns the depths of the remaining tokens in the current optimal subtree
multiset<int> dfs(Node *node) {
	multiset<int> ms;
	for (int c = 0; c < MAX; c++) 
		if (node->nxt[c]) 
			for (int num : dfs(node->nxt[c])) ms.insert(num + 1);
	
	if (node->end) {
		ms.insert(1);
		return ms;
	}

	int deepest = *ms.rbegin();
	ms.erase(--ms.end());
	cnt -= (deepest - 1);
	ms.insert(1);
	return ms;
}

int32_t main() {
	int n; cin >> n;
	string s; root = new Node();
	for (int i = 0; i < n; i++)
		cin >> s, insert(s), cnt += s.length();
	for (int c = 0; c < MAX; c++)
		if (root->nxt[c]) dfs(root->nxt[c]);
	cout << cnt << endl;
	return 0;
}