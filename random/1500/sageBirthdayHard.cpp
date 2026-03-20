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
	int last = 0, ex = 0, st = 0; 
	for (int i = 1; i <= n; i++) {
		int extra = (--lower_bound(a.begin() + 1, a.end(), a[i] + 1) - a.begin()) - i;
		int start = lower_bound(a.begin() + 1, a.end(), a[i]) - a.begin();
		int same = i - start + 1;

		int needed = 0;
		if (start <= extra)
			needed += (same + 1);
		else if (start > extra)
			needed += (i + 1 - extra);

		int j = lower_bound(a.begin() + 1, a.end(), a[i] + 1) - a.begin();
		if (n - j + 1 < needed) break;
		last = i, ex = extra, st = start;
	}

	cout << last << endl;
	int i = 1, j = last + 1;
	while (i <= last && j <= n)
		cout << a[j++] << " " << a[i++] << " ";
	while (j <= n)
		cout << a[j++] << " ";

	cout << endl;
	return 0;
}