#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;
	vector<pair<int, int>> A, B;
	vector<int> doneA(n + 1, false);
	int v;
	for (int r = 1; r <= n; r++)
		cin >> v, A.push_back({v, r});
	for (int r = 1; r <= n; r++)
		cin >> v, B.push_back({v, r});

	int a1 = A[0].first, an = A[n - 1].first;
	int b1 = B[0].first, bn = B[n - 1].first;

	int cost = 0;
	sort(A.begin(), A.end()), sort(B.begin(), B.end());
	for (auto &[b, i] : B) {
		int j = lower_bound(A.begin(), A.end(), make_pair(b, 0ll)) - A.begin();
		if (j >= n) j = n - 1;

		if (!j) {
			auto [a, k] = A[j];
			doneA[k] = true;
			cost += llabs(a - b);
		} else if (j == n - 1) {
			auto [a, k] = A[j];
			doneA[k] = true;
			cost += llabs(a - b);
		} else {
			auto [t, r] = A[j];
			auto [x, y] = A[j - 1];

			if (llabs(b - t) < llabs(b - x)) {
				doneA[r] = true;
				cost += llabs(b - t);
			} else {
				doneA[y] = true;
				cost += llabs(b - x);
			}
		}
	}

	for (auto &[a, i] : A)
		if (!doneA[i]) {
			int j = lower_bound(B.begin(), B.end(), make_pair(a, 0ll)) - B.begin();
			if (j >= n) j = n - 1;
			if (!j) {
				auto [b, k] = B[j];
				cost += llabs(a - b);
			} else if (j == n - 1) {
				auto [b, k] = B[j];
				cost += llabs(a - b);
			} else {
				auto [t, r] = B[j];
				auto [x, y] = B[j - 1];
	
				if (llabs(a - t) < llabs(a - x)) 
					cost += llabs(a - t);
				else 
					cost += llabs(a - x);
			}
			cout << i << " " << j << endl;
		}

	cout << min(cost, llabs(a1 - b1) + llabs(an - bn)) << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}