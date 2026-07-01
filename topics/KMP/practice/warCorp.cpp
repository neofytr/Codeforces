#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	string a, b; cin >> a >> b;
	int n = a.length(), m = b.length();

	vector<int> cmn(n + 2, 0), p(m + 1, 0);
	int j = p[1];
	for (int i = 2; i <= m; i++) {
		while (j > 0 && b[j + 1 - 1] != b[i - 1])
			j = p[j];
		if (b[j + 1 - 1] == b[i - 1])
			++j;
		p[i] = j;
	}

	j = 0;
	int last = 0;
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		while (j > 0 && b[j + 1 - 1] != a[i - 1])
			j = p[j];
		if (b[j + 1 - 1] == a[i - 1])
			++j;
		if (j == m) { 
			j = p[j];
			if (i - m + 1 > last)
				last = i, cnt++;
		}
	}

	cout << cnt << endl;
	return 0;
}