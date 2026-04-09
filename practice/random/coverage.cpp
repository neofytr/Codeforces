#include <bits/stdc++.h>
using namespace std;

#define int long long 

int32_t main() {
	int n, m;
	cin >> n >> m;

	int c, val;
	vector<vector<int>> arr(m + 1);
	for (int r = 1; r <= m; r++) {
		cin >> c;
		while(c--)
			cin >> val, arr[r].push_back(val);
	}

	int cnt = 0;
	for (int subset = 0; subset < (1LL << m); subset++) {
		set<int> s;
		for (int bit = 0; bit < m; bit++) {
			if (subset & (1LL << bit)) {
				for (int val : arr[bit + 1])
					s.insert(val);
			}
		}
		if (s.size() == n)
			cnt++;
	}
	cout << cnt << endl;
	return 0;
}