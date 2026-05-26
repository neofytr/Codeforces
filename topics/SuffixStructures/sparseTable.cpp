#include <bits/stdc++.h>
using namespace std;

#define LOG (int)(21) // 2^20 >= 10^6
#define MAX (int)(4 * 1e5)

int arr[MAX + 1];
int tab[LOG + 1][MAX + 1];

void build() {
	// tab[i][j] = min(arr[r] for j <= r <= j + (2^i) - 1) for 0 <= i <= LOG, 1 <= j and j + 2^i - 1 <= n
	// tab[0][j] = arr[j] for 1 <= j <= n

	// tab[i][j] = min(tab[i - 1][j], tab[i - 1][j + 2^(i - 1)]) for 0 <= i <= LOG, 1 <= j and j + 2^i - 1 <= n
	for (int j = 1; j <= n; j++)
		tab[0][j] = arr[j];
	for (int i = 1; i <= LOG; i++)
		for (int j = 1; j + (1ll << i) - 1 <= n; j++)
			tab[i][j] = min(tab[i - 1][j], tab[i - 1][j + (1ll << (i - 1))]);
}

int query(int l, int r) {
	int len = r - l + 1;
	int pw = 64 - __builtin_clzll(len) - 1;
	return min(tab[pw][l], tab[pw][r - (1ll << pw) + 1]);
}