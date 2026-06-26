#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(1e6)

// aut[j][c] is the largest prefix of p that is the same as some suffix of
// (p[1, j] + c)
int aut[MAX + 1][26];
int pi[MAX + 1];

int32_t main() {
	int n, m;
	string s, p; cin >> s >> p;

	n = s.length(), m = p.length();

	int k = 0; pi[1] = k;
	for (int i = 2; i <= m; i++) {
		while (k > 0 && p[k + 1 - 1] != p[i - 1])
			k = pi[k];
		if (p[k + 1 - 1] == p[i - 1])
			k++;
		pi[i] = k;
	}

	for (int j = 0; j <= m; j++)
		for (int c = 0; c < 26; c++)
			if (j <= m - 1 && p[j + 1 - 1] - 'a' == c)
				aut[j][c] = j + 1;
			else if (!j)
				aut[j][c] = 0;
			else 
				aut[j][c] = aut[pi[j]][c];

	int cnt = 0;
	k = 0;
	for (int i = 1; i <= n; i++) {
		k = aut[k][s[i - 1] - 'a'];
		if (k == m)
			cnt++;
	}

	cout << cnt << endl;
	return 0;
}