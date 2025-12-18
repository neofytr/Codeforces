#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n;
	cin >> n;

	vector<int> b(n + 1), f(n + 1);
	for (int r = 1; r <= n; r++) cin >> b[r], f[b[r]]++;

	for (int r = 1; r <= n; r++)
		if (f[r] % r) {
			cout << -1 << endl;
			return;
		}

	int i = 1;
	vector<int> a(n + 1), assign(n + 1);
	for (int r = 1; r <= n; r++) {
		int e = b[r];
		if (!(f[e] % e)) assign[e] = i++;
	    a[r] = assign[e], f[e]--;
	}

	for (int r = 1; r <= n; r++)
		cout << a[r] << " ";
	cout << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while(t--) {
		solve();
	}
	return 0;
}