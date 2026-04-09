#include <bits/stdc++.h>
using namespace std;

#define int long long
#define INF (int)(1e9)

int32_t main() {
	int n, m, k;
	cin >> n >> m >> k;

	vector<int> b(n + 1);
	for (int r = 1; r <= n; r++) cin >> b[r];

	priority_queue<int> pq;
	for (int r = n; r >= 2; r--)
		pq.push({b[r - 1] - b[r]});

	int res = k;
	int extra = n - k;

	while (extra--) {
		int x = pq.top();
		pq.pop();

		res -= x;
	}

	cout << res << endl;
	return 0;
}