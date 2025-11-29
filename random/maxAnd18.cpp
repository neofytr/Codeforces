#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, k;
	cin >> n >> k;

	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++)
		cin >> arr[r];

	vector<int> b(32);
	for (int r = 1; r <= n; r++)
		for (int bit = 0; bit < 32; bit++)
			if (arr[r] & (1LL << bit))
				b[bit]++;

	for (int bit = 0; bit < 32; bit++)
		b[bit] <<= bit;

	vector<pair<int, int>> v;
	for (int bit = 0; bit < 32; bit++)
		v.push_back({b[bit], bit});

	sort(v.begin(), v.end(), [](const auto &a, const auto &b) {
    	if (a.first != b.first)
        	return a.first > b.first;      // DESC on first
    	return a.second < b.second;        // ASC on second
	});

	int x = 0;
	for (auto &[val, bit] : v) {
		x |= (1LL << bit);
		if (!(--k))
			break;
	}

	cout << x << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while(t--) {
		solve();
	}
	return 0;
}