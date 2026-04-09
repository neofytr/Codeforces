#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    int n, q;
    cin >> n >> q;

    vector<int> arr(n + 1, 0);
    for (int r = 1; r <= n; r++)
        cin >> arr[r];

    vector<int> p(n + 2, 0);

    int l, r;
    while (q--) {
        cin >> l >> r;
        p[l] += 1;
        p[r + 1] -= 1;
    }

    for (int r = 1; r <= n; r++)
        p[r] += p[r - 1];

    sort(p.begin() + 1, p.end() - 1);
    sort(arr.begin() + 1, arr.end());

    int sum = 0;
    for (int r = 1; r <= n; r++)
        sum += arr[r] * p[r];
    cout << sum << endl;
    return 0;
}