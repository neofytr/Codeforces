#include <bits/stdc++.h>
using namespace std;

#define int long long 

void merge() {
	int n, m;
	cin >> n >> m;

	// a and b are guaranteed to be sorted in non-decreasing order
	vector<int> a(n + 1), b(m + 1), c(n + m + 1);
	for (int r = 1; r <= n; r++)
		cin >> a[r];
	for (int r = 1; r <= m; r++)
		cin >> b[r];

	int i = 1, j = 1;
	while (i < n || j < m) {
		if (i == n)
			c[i + j - 1] = b[j], j++;
		else if (j == m)
			c[i + j - 1] = a[i], i++;
		else {
			if (a[i] > b[j])
				c[i + j - 1] = b[j], j++;
			else 
				c[i + j - 1] = a[i], i++;
		}
	}

	for (int r = 1; r <= n + m; r++)
		cout << c[r] << " ";
	cout << endl;
}

void find() {
	int n, m, x;
	cin >> n >> m >> x;

	// a and b are guaranteed to be sorted in non-decreasing order and have distinct elements
	vector<int> a(n + 1), b(m + 1);
	for (int r = 1; r <= n; r++)
		cin >> a[r];
	for (int r = 1; r <= m; r++)
		cin >> b[r];

	// Find number of pairs (i, j) where 1 <= i <= n and 1 <= j <= m such that a[i] + b[j] = x
	int cnt = 0;
	int i = 1, j = m;
	while (i <= n && j >= 1) {
		if (b[j] > x - a[i])
			j--;
		else if (b[j] < x - a[i])
			i++;
		else if (b[j] == x - a[i])
			cout << i << " " << j << endl, cnt++, j--, i++;
	}

	cout << cnt << endl;
}

int32_t main() {
	find();
	return 0;
}
