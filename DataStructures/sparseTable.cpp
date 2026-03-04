#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(1e5)
#define LOG (18) // since 2^18 > 1e5

// tab[i][j] is the minimum value in the range [j, j + 2^i - 1]

int n;
int tab[LOG + 1][MAX + 1];
int a[MAX + 1];

void build() {
	for (int i = 1; i <= n; i++)
		tab[0][i] = a[i];

	for (int i = 1; i <= LOG; i++)
		for (int j = 1; j <= n; j++) {
			tab[i][j] = tab[i - 1][j];
			if (j + (1ll << (i - 1)) <= n)
				tab[i][j] = min(tab[i][j], tab[i - 1][j + (1ll << (i - 1))]);
		}
}

int query(int l, int r) {
	int len = r - l + 1;
	int k = 63 - __builtin_clzll(len); // the largest power of 2 <= len
	return min(tab[k][l], tab[k][r - (1ll << k) + 1]);
}

