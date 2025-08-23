#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: nusret
// URL: https://codeforces.com/gym/104114/problem/N
// Difficulty: hard
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    vector<int> update(n + 1, 0);
    for (int r = 0; r < n - 1; r++) {
        if (arr[r + 1] > arr[r]) {
            if (const int d = arr[r + 1] - arr[r]; d <= m)
                continue;
            const int nw = arr[r + 1] - m;
            const int diff = nw - arr[r];
            update[0] += diff;
            update[r + 1] -= diff;
        } else {
            if (const int d = arr[r + 1] - arr[r]; d <= m)
                continue;
            arr[r + 1] = arr[r] + m;
        }
    }

    for (int index = 1; index <= n; index++)
        update[index] += update[index - 1];
    for (int index = 0; index < n; index++)
        arr[index] += update[index];
    for (const int val : arr)
        cout << val << " ";
    cout << endl;

    return 0;
}