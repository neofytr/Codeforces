#include <bits/stdc++.h>
using namespace std;

#define int long long
#define INF (int)(1e16)

struct Line {
	double m, c;
};

struct CHT {
	vector<pair<Line, double>> v;

	void insert(double m, double c) {
		double xint = -INF;
		while (!v.empty()) {
			auto &[L, x] = v.back();
			xint = (L.c - c) / (m - L.m);
			if (xint > x) break;
			v.pop_back(); // the last line becomes obsolete
		}
		v.push_back({{m, c}, xint});
	}

	int query(double x) {
		if (!v.size()) return -1;
		int left = 0;
		int right = v.size();
		while (right != left + 1) {
			int mid = left + (right - left) / 2;
			if (v[mid].second <= x) left = mid;
			else right = mid;
		}
		
		Line L = v[left].first;
		return L.m * x + L.c;
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