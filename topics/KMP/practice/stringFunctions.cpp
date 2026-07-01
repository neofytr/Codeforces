#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	string s; cin >> s;
	int n = s.length();

	vector<int> p(n + 1, 0);
	int j = p[1];
	for (int i = 2; i <= n; i++) {
		while (j > 0 && s[j + 1 - 1] != s[i - 1])
			j = p[j];
		if (s[j + 1 - 1] == s[i - 1])
			++j;
		p[i] = j;
	}	

	for (int i = 1; i <= n; i++)
		cout << p[i] << " ";
	cout << endl;
	return 0;
}