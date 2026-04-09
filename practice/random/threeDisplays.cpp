#include <bits/stdc++.h>
using namespace std;

#define int long long 

int32_t main() {
	int n;
	cin >> n;

	vector<int> s(n + 1), c(n + 1);
	for (int r = 1; r <= n; r++) cin >> s[r];
	for (int r = 1; r <= n; r++) cin >> c[r];

	int mini = LLONG_MAX;
	for (int j = 1; j <= n; j++) {
		int minione = LLONG_MAX;
		int minitwo = LLONG_MAX;

		for (int i = 1; i <= j - 1; i++)
			if (s[i] < s[j])
				minione = min(minione, c[i]);
		for (int k = j + 1; k <= n; k++)
			if (s[j] < s[k])
				minitwo = min(minitwo, c[k]);

		if (minione != LLONG_MAX && minitwo != LLONG_MAX) 
			mini = min(mini, c[j] + minione + minitwo);
	}

	if (mini == LLONG_MAX)
		cout << -1;
	else 
		cout << mini;
	cout << endl;
}