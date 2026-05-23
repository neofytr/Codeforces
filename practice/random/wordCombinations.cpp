#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MOD (int)(1e9 + 7)
#define MAX (int)(26)

struct Node {
	int nxt[MAX];
	bool end;

	Node() {
		memset(nxt, -1, sizeof(nxt));
		end = false;
	}
};

vector<Node> trie(1);
void insert(string &s) {
	int curr = 0;
	for (int i = s.length() - 1; i >= 0; i--) {
		int c = s[i] - 'a';
		if (trie[curr].nxt[c] == -1) 
			trie[curr].nxt[c] = trie.size(), trie.push_back(Node());
		curr = trie[curr].nxt[c];
	}
	trie[curr].end = true;
}

int32_t main() {
	string s; cin >> s;
	int n = s.length();
	vector<char> str(n + 1);
	for (int i = 1; i <= n; i++) str[i] = s[i - 1];

	int k; cin >> k;
	for (int i = 1; i <= k; i++) 
		cin >> s, insert(s);
	

	vector<int> dp(n + 1);
	dp[0] = 1;
	for (int i = 1; i <= n; i++) {
		int curr = 0;
		for (int j = i; j >= 1; j--) {
			int c = str[j] - 'a';
			if (trie[curr].nxt[c] == -1) break;
			curr = trie[curr].nxt[c];
			if (trie[curr].end) {
				dp[i] += dp[j - 1];
				dp[i] %= MOD;
			}
		}
	}

	cout << dp[n] << endl;
}