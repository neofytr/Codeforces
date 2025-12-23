#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, m;
	cin >> n >> m;

	string str;
	cin >> str;
	vector<char> comm(n + 1);
	for (int r = 1; r <= n; r++) comm[r] = str[r - 1];

	set<int> black;
	vector<int> v(m + 1);
	for (int r = 1; r <= m; r++)
		cin >> v[r], black.insert(v[r]);

	int l = 1, r = 1;
	unordered_map<int, int> mp;
	while (l <= m) {
		r = l;
		int k = 0;
		while (r <= m && v[r] == v[l] + k)
			k++, r++;

		// [l, r - 1]
		for (int i = l; i <= r - 1; i++)
			mp[v[i]] = v[l] + k;
		l = r;
	}

	int curr = 1;
	for (int r = 1; r <= n; r++)
		if (comm[r] == 'A') black.insert(++curr);
		else {
			if (!mp[curr + 1])
				black.insert(++curr);
			else 
				curr = mp[curr + 1], black.insert(curr);
			
			if (mp[curr + 1])
				curr = mp[curr + 1];
			else
				curr++;
		}

	cout << black.size() << endl;
	for (int b : black)
		cout << b << " ";
	cout << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}