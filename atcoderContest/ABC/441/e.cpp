#include <bits/stdc++.h>
using namespace std;

#define int long long 

int32_t main() {
	int n;
	cin >> n;

	string s;
	cin >> s;

	vector<int> str(n + 1);
	for (int r = 1; r <= n; r++) str[r] = s[r - 1] - 'A';

	vector<int> A(n + 1, 0), B(n + 1, 0);
 	for (int r = 1; r <= n; r++)
 		A[r] += A[r - 1] + (!str[r] ? 1 : 0), B[r] += B[r - 1] + (str[r] == 1 ? 0 : 1);
	return 0;
}