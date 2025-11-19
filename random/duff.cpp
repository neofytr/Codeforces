#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int val;
    vector<int> v(1e6 + 51);
    for (int r = 1; r <= n; r++)
    	cin >> val, v[val]++;

    int res = 0;
    for (int r = 1; r <= 1e6 + 49; r++)
    	res += (v[r] & 1), v[r + 1] += (v[r] >> 1);
    cout << res << endl;
    return 0;
}
