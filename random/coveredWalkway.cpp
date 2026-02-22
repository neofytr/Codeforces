#include <bits/stdc++.h>
using namespace std;

#define int long long
#define INF (int)(1e16)

struct Line {
	int m, c;
};

struct CHT {
	vector<Line> hull;

	// slope of l < slope of l1 < slope of l2
	// returns true if int(l, l1) > int(l1, l2)
	bool check(Line &l, Line &l1, Line &l2) {
		return (l1.m - l.m) * (l1.c - l2.c) <= (l.c - l1.c) * (l2.m - l1.m);
	}

	int val(Line &l, int x) {
		return l.m * x + l.c;
	}

	void insert(int m, int c) {
		if (hull.empty() || hull.size() == 1) {
			hull.push_back({m, c});
			return;
		}

		Line l = {m, c};
		while (hull.size() >= 2) {
			Line l1 = *hull.rbegin(), l2 = *(++hull.rbegin());
			if (check(l, l1, l2)) break;
			hull.pop_back();
		}	

		hull.push_back(l);
	}

	int query(int x) {
		int n = hull.size();
		int left = 0;
		int right = n - 1;
		while (left < right) {
			int mid = left + (right - left) / 2;
			if (mid == n - 1)
				return val(hull[mid], x);

			if (val(hull[mid], x) < val(hull[mid + 1], x)) right = mid;
			else left = mid + 1;
		}
		return val(hull[left], x);
	}
};


int32_t main() {
	int n, c; cin >> n >> c;
	vector<int> arr(n + 2);
	for (int r = 1; r <= n; r++) cin >> arr[r];

	CHT cht;
	vector<int> dp(n + 1);
	dp[0] = 0;
	for (int i = 1; i <= n; i++) {
		cht.insert(-2 * arr[i], dp[i - 1] + arr[i] * arr[i]);
		dp[i] = c + arr[i] * arr[i] + cht.query(arr[i]);
	}

	cout << dp[n] << endl;
	return 0;
}