#include <bits/stdc++.h>
using namespace std;

#define int long long
#define NMAX (int)(2 * 1e5)
#define ceil(x) (((x) + 1) / 2)

int wt[NMAX + 1];
pair<int, int> p[NMAX + 1];

void solve() {
	int n, w;
	cin >> n >> w;

	for (int r = 1; r <= n; r++)
		cin >> wt[r];

	for (int r = 1; r <= n; r++)
		if (ceil(w) <= wt[r] && wt[r] <= w) {
			cout << 1 << endl;
			cout << r << endl;
			return;
		}

	bool all = true;
	for (int r = 1; r <= n; r++)
		if (wt[r] <= w) {
			all = false;
			break;
		}

	if (all) {
		cout << -1 << endl;
		return;
	}

	for (int r = 1; r <= n; r++) p[r] = {wt[r], r};
	sort(p + 1, p + n + 1);

	int sum = 0;
	vector<int> e;
	for (int r = 1; r <= n; r++) {
		if (sum + p[r].first >= ceil(w)) { 
			sum += p[r].first;
			e.push_back(p[r].second);
			break;
		}

		e.push_back(p[r].second), sum += p[r].first;
	}

	if (sum >= ceil(w) && sum <= w) {
		cout << e.size() << endl;
		for (int idx : e)
			cout << idx << " ";
		cout << endl;
		return;
	}

	cout << -1 << endl;
}

int32_t main() { 
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
} 