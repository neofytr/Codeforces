#include <bits/stdc++.h>
using namespace std;

#define int long long 

bool isrep(int x) {
	string num = to_string(x);
	int len = num.length();
	for (int sz = 1; sz <= (len >> 1); sz++) {
		bool is = true;
		for (int r = 0; r < len; r += sz) 
			if (num.substr(r, sz) != num.substr(0, sz)) {
				is = false;
				break;
			}
		if (is)
			return true;
	}
	return false;
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
			if (isrep(r))
				sum += r;
	}
	cout << sum << endl;
	return 0;
}