#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n;
	cin >> n;
	vector<int> arr(n), p(n + 1, 0);
	for (int &val : arr)
		cin >> val;

	for (int r = 1; r <= n; r++)
		p[r] += p[r - 1] + arr[r - 1];

	string str;
	cin >> str;

	int l = 0, r = n - 1, cnt = 0;
	while (l < r)
		if (str[l] != 'L')
			l++;
		else if (str[r] != 'R')
			r--;
		else 
			cnt += (p[r + 1] - p[l]), r--, l++;
	cout << cnt << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}