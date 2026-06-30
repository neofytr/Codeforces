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

	if (w == 1) {
		cout << n << endl;
		return 0;
	}

	if (n == 1 || w > n) {
		cout << 0 << endl;
		return 0;
	}

	vector<int> diff_a(n), diff_b(n);
	for (int i = 1; i <= n - 1; i++)
		diff_a[i] = a[i + 1] - a[i];
	for (int i = 1; i <= w - 1; i++)
		diff_b[i] = b[i + 1] - b[i];

	vector<int> p(w, 0);
	int j = 0;
	for (int i = 2; i <= w - 1; i++) {
		while (j > 0 && diff_b[j + 1] != diff_b[i])
			j = p[j];
		if (diff_b[j + 1] == diff_b[i])
			++j;
		p[i] = j;
	}

	int cnt = 0;;
	j = 0;
	for (int i = 1; i <= n - 1; i++) {
		while (j > 0 && diff_b[j + 1] != diff_a[i])
			j = p[j];
		if (diff_b[j + 1] == diff_a[i])
			++j;
		if (j == w - 1) 
			cnt++, j = p[j];
	}
	cout << cnt << endl;
	return 0;
}