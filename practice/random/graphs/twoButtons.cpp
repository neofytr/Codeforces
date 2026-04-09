#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n, m; cin >> n >> m;

	vector<int> dist((int)2 * 1e5, LLONG_MAX);
	queue<int> que;
	que.push(n);
	dist[n] = 0;
	while (!que.empty()) {
		int x = que.front(); que.pop();
		int d = dist[x];
		if (x == m) {
			cout << dist[x] << endl;
			return 0;
		}
		if (!x)
			continue;
		if (dist[x - 1] > d + 1)
			dist[x - 1] = d + 1, que.push(x - 1);
		if (x < m && dist[2 * x] > d + 1)
			dist[2 * x] = d + 1, que.push(2 * x);
	}
	return 0;
}