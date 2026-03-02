#include <bits/stdc++.h>
using namespace std;

#define int long long

int pw(int base, int exp) {
	int res = 1;
	while (exp) {
		if (exp & 1) res *= base;
		base *= base;
		exp >>= 1;
	}
	return res;
}

int32_t main() {
	int k;
	cin >> k;

	string s = "codeforces";

	int left = 0, right = 44;

	while (right != left + 1) {
		int mid = left + ((right - left) >> 1);
		if (pw(mid, 10) > k) right = mid;
		else left = mid;
	}

	for (int i = 0; i <= 10; i++) {
		if (pw(left, 10 - i) * pw(left + 1, i) >= k) {
			for (int j = 0; j < 10; j++) {
				int times = (j < 10 - i) ? left : (left + 1);
				for (int t = 0; t < times; t++)
					cout << s[j];
			}
			cout << "\n";
			break;
		}
	}

	return 0;
}