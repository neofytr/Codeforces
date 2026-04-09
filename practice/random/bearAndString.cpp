#include <bits/stdc++.h>
using namespace std;

#define int long long 

int32_t main() {
	ios::sync_with_stdio(false);
    cin.tie(nullptr);

	int n, k;
	cin >> n >> k;

	string str;
	cin >> str;

	// d = 'z' - 'b' 25 - 1 = 24

	string fin;
	int left = k;
	for (char c : str) {
		if (!left) {
			fin.push_back(c);
			continue;
		}

		if ('z' - c >= c - 'a') {
			int d = 'z' - c;
			if (left >= d)
				left -= d, fin.push_back('z');
			else if (d > left)
				fin.push_back(c + left), left = 0;
		} else {
			int d = c - 'a';
			if (left >= d)
				left -= d, fin.push_back('a');
			else if (left < d)
				fin.push_back(c - left), left = 0;
		}
	}

	if (left)
		cout << -1 << endl;
	else {
		int s = 0;
		for (int r = 0; r < str.length(); r++)
			s += abs(str[r] - fin[r]);

		if (s != k)
			return 0;
		cout << fin << endl;
	}
	return 0;
}