#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n;
	cin >> n;

	vector<int> b(n + 1);
	for (int r = 1; r <= n; r++) cin >> b[r];
	unordered_map<int, int> f;

	for (int r = 1; r <= n - 1; r++) {
		if (b[r + 1] % b[r]) {
			vector<int> x;
			for (int i  = 1; i * i <= b[r + 1]; i++)
				if (!(b[r + 1] % i) && !(b[r] % i)) {
					x.push_back(i);
					int k = b[r + 1] / i;
					if (i != k && !(b[r] % k)) x.push_back(k);
				}

			for (int e : x)
				f[e]++;
		} else {
			int d = b[r + 1] / b[r];
		}
		

		if (b[r + 1] % b[r])
			for (int e : x)
				f[b[r] / e]++;
		else
			for (int e : x)
				f[e]++;
	}	

	vector<int> res;
	for (auto &[val, cnt] : f) 
		if (cnt == n - 1) 
			res.push_back(val);
	
	int maxi = LLONG_MIN;
	for (int e : res)
		maxi = max(maxi, e);
	cout << maxi << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}