#include <bits/stdc++.h>
using namespace std;

#define int long long 

int32_t main() {
	int n;
	cin >> n;

	int last = 1, val;
	int poscnt = 1, negcnt = 0;
	for (int r = 1; r <= n; r++) {
		cin >> val;
		if (last * val > 0) {
			last = 1;
			poscnt++;
		} else {
			last = -1;
			negcnt++;
		}
	}

	cout << poscnt * negcnt << " " << (poscnt * (poscnt - 1)) / 2 + (negcnt * (negcnt - 1)) / 2 << endl;
}

int32_t main2() {
	int n;
	cin >> n;

	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r];

	vector<int> p(n + 1);
	p[0] = 1;
	for (int r = 1; r <= n; r++)
		if (arr[r] * p[r - 1] > 0)
			p[r] = 1;
		else 
			p[r] = -1;

	int poscnt = 0;
	unordered_map<int, int> f;
	f[1]++;
	for (int r = 1; r <= n; r++) {
		poscnt += f[p[r]];
		f[p[r]]++;
	}

	cout << (n * (n + 1)) / 2 - poscnt << " " << poscnt << endl;

	return 0;
}