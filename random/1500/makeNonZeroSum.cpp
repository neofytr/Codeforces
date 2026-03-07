#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;
	vector<int> a(n + 1);

	int S = 0; int sign = 1;
	for (int i = 1; i <= n; i++) 
		cin >> a[i], S += sign * a[i], sign *= -1;

	vector<pair<int, int>> two, minustwo;
	for (int i = 2; i <= n; i += 2) {
		if (a[i] == 1) two.push_back({i, i});
		else if (a[i] == -1) minustwo.push_back({i, i});
	}

	if (!S) {
		cout << 1 << endl;
		cout << 1 << " " << n << endl;
		return;
	}

	if (llabs(S) & 1) {
		cout << -1 << endl;
		return;
	}

	vector<pair<int, int>> segs;
	if (S < 0) {
		S *= -1;
		int s = 0;
		int k = (S - s) / 2;
		for (int i = 0; i < min(k, (int)two.size()); i++) {
			auto [l, r] = two[i];
			segs.push_back({l, r});
			s += 2;
		}

		if (s != S) {
			cout << -1 << endl;
			return;
		}
	} else {
		int s = 0;
		int k = (S - s) / 2;
		for (int i = 0; i < min(k, (int)minustwo.size()); i++) {
			auto [l, r] = minustwo[i];
			segs.push_back({l, r});
			s += 2;
		}

		if (s != S) {
			cout << -1 << endl;
			return;
		}
	}

	sort(segs.begin(), segs.end());
	int start = 1;
	vector<pair<int, int>> final;
	for (int i = 0; i < segs.size(); i++) {
		auto [l, r] = segs[i];
		if (start < l) final.push_back({start, l - 1});
		start = r + 1;
		final.push_back({l, r});
	}

	if (start <= n) final.push_back({start, n});

	sort(final.begin(), final.end());
	cout << final.size() << endl;
	for (auto &[l, r] : final)
		cout << l << " " << r << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}