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
		tab[0][i] = i;
}

