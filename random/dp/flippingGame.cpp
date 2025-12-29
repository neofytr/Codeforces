#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (100)

int32_t main() {
    int n;
    cin >> n;

    // If we apply the operation to arr[l, r],
    // -(p[r] - p[l - 1]) + ((r - l + 1) - (p[r] - p[l - 1]))
    // r - l + 1 - 2 * p[r] + 2 * p[l - 1]
    // r - 2 * p[r] - ((l - 1) - 2 * p[l - 1])

    int p = 0, v;
    int mini = 0 - 2 * p;
    int maxi = LLONG_MIN;
    for (int r = 1; r <= n; r++)
        cin >> v, p += v, maxi = max(maxi, r - 2 * p - mini), mini = min(mini, r - 2 * p);

    cout << p + maxi << endl;
    return 0;
}