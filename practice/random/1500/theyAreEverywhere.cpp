#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n; cin >> n;
	string str; cin >> str;

	vector<char> a(n + 1);
	for (int r = 1; r <= n; r++) a[r] = str[r - 1];

	set<char> g;
	for (int r = 1; r <= n; r++) g.insert(a[r]);
	int c = g.size();

	int l = 1;
	int mini = LLONG_MAX;
	unordered_map<char, int> f;
	set<char> s;
	for (int r = 1; r <= n; r++) {
		s.insert(a[r]), f[a[r]]++;
		while (l <= r && s.size() >= c) {
			if (!(--f[a[l]])) s.erase(a[l]);
			l++;
		}

		// [l - 1, r]
		if (l - 1 >= 1) 
			mini = min(mini, r - l + 2);
	}

	cout << mini << endl;
}