#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n; cin >> n;
	vector<int> a(n + 1, 0);
	for (int i = 1; i <= n; i++) cin >> a[i];

	if (n == 1) {
		cout << 0 << endl;
		cout << a[1] << endl;
		return 0;
	}

	if (n == 2) {
		cout << 0 << endl;
		cout << a[1] << " " << a[2] << endl;
		return 0;
	}

	sort(a.begin() + 1, a.end());
	int last = 0;

	for (int i = 1; i <= n; i++) {
		auto it = lower_bound(a.begin() + 1, a.end(), a[i] + 1);

		int extra = 0;
		if (it != a.begin() + 1) {
			extra = (it - 1 - a.begin()) - i;
		}

		int start = lower_bound(a.begin() + 1, a.end(), a[i]) - a.begin();
		int same = i - start + 1;

		int needed = 0;
		if (start <= extra)
			needed += (same + 1);
		else
			needed += (i + 1 - extra);

		int j = it - a.begin();
		if (n - j + 1 < needed) break;
		last = i;
	}

	cout << last << endl;

	vector<int> res;
	int i = 1, j = n - last; 
	while (i <= last) {
		res.push_back(a[j++]); 
		res.push_back(a[i++]); 
	}
	res.push_back(a[j++]);
	
	for (int k = last + 1; k < n - last; k++) {
		res.push_back(a[k]);
	}
	
	for (auto x : res) cout << x << " ";
	cout << endl;

	return 0;
}