#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	string t; cin >> t;

	int n = t.length();
	vector<int> p(n + 1, 0);

	int j = p[1];
	for (int i = 2; i <= n; i++) {
		while (j > 0 && t[j + 1 - 1] != t[i - 1])
			j = p[j];
		if (t[j + 1 - 1] == t[i - 1])
			++j;
		p[i] = j;
	}

	if ((n & 1) && p[n] >= ((n + 1) >> 1))
		cout << "YES" << endl << t.substr(0, p[n]) << endl;
	else if (!(n & 1) && p[n] >= ((n + 2) >> 1))
		cout << "YES" << endl << t.substr(0, p[n]) << endl;
	else 
		cout << "NO" << endl;
	return 0;
}
