#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n;
	cin >> n;

	int v;
	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++)
		cin >> v, arr[r] = (v >= 1 ? 1 : -1);

	int pcnt = 1;
	int ncnt = 0;

	int p = 1;
	int cnt = 0;
	for (int r = 1; r <= n; r++) {
		p *= arr[r];
		if (p > 0) cnt += pcnt;
		else cnt += ncnt;

		if (p > 0) pcnt++;
		else ncnt++;
	}

	cout << cnt << endl;
	return 0;
}