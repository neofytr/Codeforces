#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define MAX (int)(2 * 1e5)
#define INF (int)(1e16)

int arr[MAX + 1];

void solve() {
	int n;
	cin >> n;

	for (int r = 1; r <= n; r++) cin >> arr[r];
	int x = INF, y = INF;

	int c = 0;
	for (int r = 1; r <= n; r++) {
		if (x > y) swap(x, y);

		if (arr[r] <= x) x = arr[r];
		if (arr[r] > y) x = arr[r], c++;
		if (x < arr[r] && arr[r] <= y) y = arr[r];
	}

	cout << c << endl;
}

int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int t;
	cin >> t;
	while (t--) solve();
	return 0;
}
