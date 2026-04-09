#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n;
	cin >> n;

	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r];

	vector<int> cnt(32);
	for (int bit = 0; bit < 32; bit++) 
		for (int r = 1; r <= n; r++)
			if (arr[r] & (1LL << bit))
				cnt[bit]++;

	int g = 0;
	for (int bit = 0; bit < 32; bit++)
		g = gcd(g, cnt[bit]);

	for (int k = 1; k <= n; k++)
		if (!(g % k))
			cout << k << " ";
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