#include <bits/stdc++.h>
using namespace std;

#define int long long 

int32_t main() {
	int n, m;
	cin >> n >> m;

	vector<int> a(n + 1), b(m + 1);
	for (int r = 1; r <= n; r++) cin >> a[r];
	for (int r = 1; r <= m; r++) cin >> b[r];

	sort(a.begin() + 1, a.end());
	sort(b.begin() + 1, b.end());

	int cnt = 0;
	int i = 1, j = 1;
	int x = 1, y = 1;
	while (i <= n && j <= m) {
		while (i <= n - 1 && a[i + 1] == a[i])
			i++;
		while(j <= m - 1 && b[j + 1] == b[j])
			j++;

		if (a[i] == b[j])
			cnt += (i - x + 1) * (j - y + 1), i++, j++, x = i, y = j;
		else if (a[i] > b[j])
			j++, y = j;
		else if (a[i] < b[j])
			i++, x = i;
	}
	cout << cnt << endl;
	return 0;
}