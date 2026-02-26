#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;

		vector<long long> w(n + 1);
		for (int i = 1; i <= n; i++) cin >> w[i];

		vector<int> deg(n + 1, 0);
		for (int i = 0; i < n - 1; i++) {
			int u, v;
			cin >> u >> v;
			deg[u]++;
			deg[v]++;
		}

		long long base = 0;
		for (int i = 1; i <= n; i++) base += w[i];

		vector<long long> extras;
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j < deg[i] - 1; j++) {
				extras.push_back(w[i]);
			}
		}

		sort(extras.begin(), extras.end(), greater<long long>());

		long long cur = base;
		int ptr = 0;

		for (int k = 1; k <= n - 1; k++) {
			if (ptr < (int)extras.size()) {
				cur += extras[ptr++];
			}
			cout << cur << (k == n - 1 ? '\n' : ' ');
		}
	}

	return 0;
}