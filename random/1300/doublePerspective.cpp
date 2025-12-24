#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n;
	cin >> n;

	vector<pair<int, int>> p(n + 1);
	for (int r = 1; r <= n; r++) cin >> p[r].first >> p[r].second;

	vector<pair<int, int>> first, second;
	for (int r = 1; r <= n; r++) first.push_back({p[r].first, r}), second.push_back({p[r].second, r});

	sort(first.begin(), first.end());
	vector<pair<int, vector<int>>> res;
	int left = -1, right = -1;
	for (int f = 0; f < n; r++) {
		int idx = first[f].second;
		left = first[f].first;
		right = p[idx].second;

		int len = 0;
		vector<int> indices;
		while (true) {
			len += (right - left + 1), indices.push_back(idx);
			auto itr = lower_bound(first.begin(), first.end(), make_pair(right, 0));
			if (itr == first.end())
				break;
			int t = LLONG_MIN;
			for (auto it = itr; it != first.end(); ++it) {
				int tmp = it->second;
				int l = p[tmp].first, r = p[tmp].second;
				if (r - l + 1 > t)
					idx = tmp, left = l, right = r;
			}

		}

		res.push_back({len, indices});
	}

	sort(res.rbegin(), res.rend());
	cout << (res.begin())->first;
	for (int r : (res.begin())->second)
		cout << r << " ";
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