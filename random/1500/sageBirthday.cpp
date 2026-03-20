#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n; cin >> n;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; i++) cin >> a[i];

	sort(a.begin() + 1, a.end());
	cout << (n - 1) / 2 << endl;

	int i = n / 2 + 1;
	int j = 1;
	while (i <= n && j <= n / 2) 
		cout << a[i++] << " " << a[j++] << " ";
	
	if (n & 1) cout << a[i];
	cout << endl;
	return 0;
}