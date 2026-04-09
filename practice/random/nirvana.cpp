#include <bits/stdc++.h>
using namespace std;

#define int long long 

int pw(int base, int exp) {
	int res = 1; 
	while(exp) {
		if (exp & 1)
			res = res * base;
		base = base * base;
		exp >>= 1;
	}
	return res;
}

int32_t main() {
	int n;
	cin >> n;

	vector<int> digs;
	while(n) {
		digs.push_back(n % 10);
		n /= 10;
	}

	reverse(digs.begin(), digs.end());
	int maxi = LLONG_MIN;
	for (int r = 0; r < digs.size(); r++) {
		if (!r) {
			int num = digs[0] - 1;
			if (!num)
				num = 1;

			num *= pw(9, (digs.size() - 1));
			maxi = max(maxi, num);
		} else {
			int num = digs[r] - 1;
			if (!num)
				continue;
			for (int i = 0; i < r; i++)
				num *= digs[i];
			num *= pw (9, digs.size() - r - 1);
			maxi = max(maxi, num);
		}
	}

	int num = 1;
	for (int r : digs)
		num *= r;
	maxi = max(num, maxi);
	cout << maxi << endl;
	return 0;
}