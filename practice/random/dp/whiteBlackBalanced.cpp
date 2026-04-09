#include <bits/stdc++.h>
using namespace std;

#define int long long 

int white(int node, string &s, vector<int> &w, vector<vector<int>> &child) {
	if (child[node].empty())
		return w[node] = (s[node - 1] == 'W' ? 1 : 0);

	int res = 0;
	for (int c : child[node])
		res += white(c, s, w, child);

	return w[node] = res + (s[node - 1] == 'W' ? 1 : 0);
}

int black(int node, string &s, vector<int> &b, vector<vector<int>> &child) {
	if (child[node].empty())
		return b[node] = (s[node - 1] == 'B' ? 1 : 0);

	int res = 0;
	for (int c : child[node])
		res += black(c, s, b, child);

	return b[node] = res + (s[node - 1] == 'B' ? 1 : 0);
}

void solve() {
	int n;
	cin >> n;

	int p;
	vector<vector<int>> child(n + 1);
	for (int c = 2; c <= n; c++)
		cin >> p, child[p].push_back(c);

	string s;
	cin >> s;

	vector<int> w(n + 1); // w[r] is the number of white vertices in the subtree rooted at r
	vector<int> b(n + 1); // b[r] is the number of black vertices in the subtree rooted at r

	white(1, s, w, child);
	black(1, s, b, child);
	int cnt = 0;

	for (int r = 1; r <= n; r++)
		if (b[r] == w[r]) cnt++;

	cout << cnt << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}

	return 0;
} 