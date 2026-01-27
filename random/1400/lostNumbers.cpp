#include <bits/stdc++.h>
using namespace std;

#define int long long

int arr[7] = {0, 4, 8, 15, 16, 23, 42};
int32_t main() {
	unordered_map<int, pair<int, int>> f;
	unordered_map<int, set<int>> g;

	for (int i = 1; i <= 6; i++)
		for (int j = i + 1; j <= 6; j++) {
		 	int p = arr[i] * arr[j];
		 	f[p] = {arr[i], arr[j]};
		 	g[arr[i]].insert(p), g[arr[j]].insert(p);
		}

	int p[7];

	int a, b;
	cout << "?" << " " << 1 << " " << 2 << endl;
	cin >> a;
	cout << "?" << " " << 2 << " " << 3 << endl;
	cin >> b;

	auto [c, d] = f[a];
	if (g[c].find(b) != g[c].end()) 
		p[1] = d, p[2] = c, p[3] = b / p[2];
	else 
		p[1] = c, p[2] = d, p[3] = b / p[2];
	
	cout << "?" << " " << 4 << " " << 5 << endl;
	cin >> a;
	cout << "?" << " " << 5 << " " << 6 << endl;
	cin >> b;

	c = f[a].first, d = f[a].second;
	if (g[c].find(b) != g[c].end()) 
		p[4] = d, p[5] = c, p[6] = b / p[5];
	else 
		p[4] = c, p[5] = d, p[6] = b / p[5];

	cout << "! ";
	for (int r = 1; r <= 6; r++)
		cout << p[r] << " ";
	cout << endl;
	return 0;
}