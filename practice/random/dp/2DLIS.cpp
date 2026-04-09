#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n;
	cin >> n;

	vector<pair<int, int>> p(n + 1);
	for (int r = 1; r <= n; r++)
		cin >> p[r].first >> p[r].second;

	sort(p.begin() + 1, p.end(), [](const pair<int, int> &one, const pair<int, int> &two) {
		if (one.first < two.first) return true;
		if (one.first == two.first && one.second > two.second) return true;
		return false;
	});

	vector<int> last(n + 2, LLONG_MAX);
	last[0] = LLONG_MIN;

	for (int r = 1; r <= n; r++) {
		int left = 0;
		int right = n + 1;

		int h = p[r].second;
		while (right != left + 1) {
			int mid = left + (right - left) / 2;
			if (last[mid] < h) left = mid;
			else right = mid;
		}

		last[left + 1] = h;
	}

	for (int r = n; r >= 1; r--)
		if (last[r] != LLONG_MAX) {
			cout << r << endl;
			return 0;
		}
	return 0;
}