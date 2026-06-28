#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n, w; cin >> n >> w;
	vector<int> a(n + 1), b(w + 1);
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 1; i <= w; i++)
		cin >> b[i];

	vector<int> p(w + 1, 0);
	int j = 0;
	for (int i = 2; i <= w; i++) {
		while (j > 0 && b[j + 1] != b[i])
			j = p[j];
		if (b[j + 1] == b[i])
			++j;
		p[i] = j;
	}

	int x = 0;
	j = 0;
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		while (j > 0 && b[j + 1] + x != a[i])
			j = p[j];
		if (b[j + 1] + x == a[i])
			++j;
		if (!j) 
			j = 1, x = a[i] - b[j];
		cout << i << " " << j << " " << x << endl;
		if (j == w)
			j = p[j], cnt++;
	}

	cout << cnt << endl;
	return 0;
}