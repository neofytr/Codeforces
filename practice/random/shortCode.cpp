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
	}
}


int32_t main() {
	int n; cin >> n;
	string s;
	root = new Node(); 
	for (int i = 1; i <= n; i++) cin >> s, insert(s);
	return 0;
} 