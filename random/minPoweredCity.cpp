#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n, r, k;
	cin >> n >> r >> k;

	vector<int> stations(n + 1);
	for (int i = 1; i <= n; i++) cin >> stations[i];

	vector<int> p(n + 2, 0);
	for (int i = 1; i <= n; i++) {
		int left = max(1LL, i - r);
		int right = min(n, i + r);

		p[left] += stations[i];
		p[right + 1] -= stations[i];
	}

	for (int i = 1; i <= n; i++)
		p[i] += p[i - 1];

	vector<int> add(n + 2, 0);
	auto can = [&](int x) -> bool{
		// can the minimum power be made atleast x?
		// , or equivalently, can the power of all cities be made >= x

		fill(add.begin(), add.end(), 0LL);
		int req = 0;
		for (int i = 1; i <= n; i++) {
			add[i] += add[i - 1];
			int curr = p[i] + add[i];
			if (curr < x) {
				req += (x - curr);
				add[i] += (x - curr);
				add[min(n, i + 2 * r) + 1] -= (x - curr);
			}
		}
		return req <= k;
	};	

	int left = 0; // minimum power can be atleast 0
	int right = 1e18 + 1; // a decent upper bound; minimum power cannot be atleast this

	while (right != left + 1) {
		int mid = left + (right - left) / 2;
		if (can(mid))
			left = mid;
		else 
			right = mid;
	}
	cout << left << endl;
	return 0;
}