#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl "\n"

void solve() {
	int n; cin >> n;
	vector<int> a(n + 1), p(n + 1);
	for (int i = 1; i <= n; i++) cin >> a[i];

	if (a[n] == 1) {
		cout << "NO" << endl;
		return;
	}

	int i = n; 
	while (i >= 0) {
		if (!a[i]) {
			p[n - i + 1] = 0;
			i--;
			continue;
		}

		int j = i;
		while (j >= 0 && a[j])
			j--;

		int len = i - j;


		i = j;
	}
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}