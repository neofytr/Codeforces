#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define double long double
#define MAX (int)(5 * 1e5)
#define INF (int)(1e18)

int vec[MAX + 1];
int p[MAX + 1];

auto cmp = [](const pair<double, int> &a, const pair<double, int> &b) -> bool {
	if (a.first < b.first) return true;
	if (a.first == b.first && a.second < b.second) return true;
	return false;
};

void solve(int t) {
	int n;
	double f;
	cin >> n >> f;

	string str;
	cin >> str;

	p[0] = 0;
	for (int r = 1; r <= n; r++) {
		vec[r] = str[r - 1] - '0';
		p[r] = p[r - 1] + vec[r];
	}

	set<pair<double, int>, decltype(cmp)> s(cmp);
	set<pair<double, int>, decltype(cmp)> res(cmp);

	for (int r = 1; r <= n; r++) {
		s.insert({p[r - 1] - (r - 1) * f, r});

		double x = p[r] - r * f;
		auto itr = s.lower_bound({x, INF});
		if (itr != s.end()) {
			auto [v, idx] = *itr;
			double g = (double)(p[r] - p[idx - 1]) / (r - idx + 1) - f;
			res.insert({abs(g), idx});
		}

		if (itr != s.begin()) {
			auto [v1, idx1] = *(--itr);
			double g = (double)(p[r] - p[idx1 - 1]) / (r - idx1 + 1) - f;
			res.insert({abs(g), idx1});
		}
	}

	cout << "Case #" << t << ": ";
	cout << res.begin()->second - 1 << endl;
}

int32_t main() {
	int t;
	cin >> t;
	for (int r = 1; r <= t; r++) {
		solve(r);
	}
	return 0;
}
