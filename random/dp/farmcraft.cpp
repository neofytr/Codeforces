#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define MAX (int)(5 * 1e5)

int c[MAX + 1];
vector<int> tree(MAX + 1);

int32_t main() {
	int n;
	cin >> n;

	int a, b;
	for (int r = 1; r <= n - 1; r++)
		cin >> a >> b, tree[a].push_back(b), tree[b].push_back(a);
	return 0;
}