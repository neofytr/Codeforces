#include <bits/stdc++.h>
using namespace std;

#define int long long 

int32_t main() {
	int n;
	cin >> n;

	string str;
	cin >> str;

	bool done = false;
	for (int r = 0; r < n - 1; r++) {
		if (str[r + 1] < str[r]) {
			str.erase(r, 1);
			done = true;
			break;
		}
	}

	if (!done)
		str.erase(n - 1, 1);

	cout << str << endl;
	return 0;
}