#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (5 * 1e5)

vector<int> graph[MAX + 1];

int tree[4 * MAX + 1];
int lin[MAX + 1]

int32_t main() {
	int n; cin >> n;
	int a, b;
	for (int i = 1; i <= n - 1; i++)
		cin >> a >> b, graph[a].push_back(b), graph[b].push_back(a);
	return 0;
}