#include <bits/stdc++.h>
using namespace std;

#define int long long 

int32_t main() {
	int n;
	cin >> n;

	unordered_map<int, int> mp;
	vector<int> arr(n + 1), p(n + 1);
	for (int r = 1; r <= n; r++)
		cin >> arr[r], mp[arr[r]] = r;

	string str;
	cin >> str;

	p[0] = 0;
	for (int r = 1; r <= n - 1; r++)
		p[r] = p[r - 1] + (str[r - 1] == '1' ? 1 : 0);


	for (int r = 1; r <= n; r++) {
		if (arr[r] == r)
			continue;
		int lt = r;
		int rt = mp[r];

		lt = min(r, mp[r]);
		rt = max(r, mp[r]);

		// all ones in [lt, rt - 1]
		if (p[rt - 1] - p[lt - 1] != rt - lt) {
			cout << "NO" << endl;
			return 0;
		}
	}

	cout << "YES" << endl;
	return 0;
}