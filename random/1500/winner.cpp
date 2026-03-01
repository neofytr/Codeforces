#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n; cin >> n;
	unordered_map<string, unordered_map<int, int>> f;
	unordered_map<string, int> g;

	for (int i = 1; i <= n; i++) {
		string str; int p;
		cin >> str >> p;
		g[str] += p;

		int &t = f[str][g[str]];
		if (!t) t = i;
	}

	int maxi = LLONG_MIN;
	for (auto &[str, p] : g)
		maxi = max(maxi, p);

	int t = LLONG_MAX;
	string s;
	for (auto &[str, p] : g)
		if (p == maxi) {
			int j = LLONG_MAX;
			for (auto &[sc, time] : f[str])
				if (sc >= maxi) j = min(j, time);

			if (j < t)
				t = j, s = str;
		}

	cout << s << endl;
	return 0;
}