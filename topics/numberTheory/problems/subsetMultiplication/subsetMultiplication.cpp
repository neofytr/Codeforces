#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: subsetMultiplication
// URL: https://codeforces.com/problemset/problem/2124/C
// Difficulty: hard
// Tags:
// Strategy:

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> arr(n);
        for (int &val : arr)
            cin >> val;

        int l = 1;
        for (int r = 0; r < n - 1; r++) {
            if (arr[r + 1] % arr[r]) {
                const int g = gcd(arr[r], arr[r + 1]);
                l = lcm(l, arr[r] / g);
            }
        }
        cout << l << endl;
    }
    return 0;
}
