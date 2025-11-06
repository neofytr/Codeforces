#include <bits/stdc++.h>
using namespace std;

#define int long long 

int32_t main() {
	int n, m;
	cin >> n >> m;

	vector<int> a(n + 1), b(m + 1); 
	for (int r = 1; r <= n; r++)
		cin >> a[r];
	for (int r = 1; r <= m; r++)
		cin >> b[r];

	int sum = 0;
	int r = 1;
	for (int j = 1; j <= m; j++) {
		while (r <= n && sum + a[r] < b[j])
			sum += a[r++];
		cout << r << " " << b[j] - sum << endl;
	}
	return 0;
}	