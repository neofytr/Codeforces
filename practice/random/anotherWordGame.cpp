#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(26)

struct Node {
	Node *nxt[MAX];
	int end; int w;
	Node() {
		for (int i = 0; i < MAX; i++) nxt[i] = nullptr;
		end = false; w = 0;
	}
};

Node *root;
void insert(string &s, int w) {
	Node *curr = root;
	for (int i = s.length() - 1; i >= 0; i--) {
		int c = s[i] - 'a';
		if (!curr->nxt[c]) curr->nxt[c] = new Node();
		curr = curr->nxt[c];
	}
	curr->end = true, curr->w = max(w, curr->w);
}

void solve(int t) {
	int n, p; cin >> n >> p;
	string s; int w;
	root = new Node();
	for (int i = 1; i <= n; i++) 
		cin >> s >> w, insert(s, w);

	cin >> s;
	int m = s.length();
	vector<int> str(m + 1);
	for (int i = 1; i <= m; i++) str[i] = s[i - 1] - 'a';

	vector<int> dp(m + 1, LLONG_MIN);
	dp[0] = 0;
	set<int> f; f.insert(dp[0] + p * 0);
	for (int i = 1; i <= m; i++) {
		Node *curr = root;
		for (int j = i; j >= 1; j--) {
			int c = str[j];
			if (!curr->nxt[c])
				break;
			curr = curr->nxt[c];
			if (curr->end && dp[j - 1] != LLONG_MIN)
				dp[i] = max(dp[i], dp[j - 1] + curr->w);
		}

		if (!f.empty())
			dp[i] = max(dp[i], *f.rbegin() - p * i);
		if (dp[i] != LLONG_MIN)
			f.insert(dp[i] + p * i);
	}

	cout << "Case " << t << ": " << dp[m] << endl;
}

int32_t main() {
	int t; cin >> t;
	for (int i = 1; i <= t; i++) solve(i);
	return 0;
}