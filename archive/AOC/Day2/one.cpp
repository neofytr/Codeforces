#include <bits/stdc++.h>
using namespace std;

#define int long long 

bool isinvalid(int x) {
	int y = x, d = 0;
	vector<int> dig(15, 0);
	while (y)
		d++, dig[d] = y % 10, y /= 10;
	if (d & 1)
		return false;

	for (int i = 1; i <= (d >> 1); i++)
		if (dig[i] != dig[i + (d >> 1)])
			return false;
	return true;
}

int32_t main() {
	string str;
	int sum = 0;
	while (cin >> str) {
		int left, right;
		char dash;
		stringstream ss(str);
		ss >> left >> dash >> right;

		for (int r = left; r <= right; r++)
			if (isinvalid(r))
				sum += r;
	}
	cout << sum << endl;
	return 0;
}