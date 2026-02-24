#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(1e5)

int n;  
int a[MAX + 1], b[MAX + 1];
int dp[MAX + 1];

typedef pair<int, int> Line;

int32_t main() {
	cin >> n;
	for (int r = 1; r <= n; r++) cin >> a[r];
	for (int r = 1; r <= n; r++) cin >> b[r];
	return 0;
}