#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    int n, k;
    cin >> n >> k;

    vector<int> arr(n + 1);
    for (int r = 1; r <= n; r++)
        cin >> arr[r];

    vector<int> prefix(n + 1, 0);
    for (int r = 1; r <= n; r++)
        prefix[r] += prefix[r - 1] + arr[r];

    int sum = 0;
    for (int week = 1; week <= n - k + 1; week++) {
        sum += prefix[week + k - 1] - prefix[week - 1];
    }

    cout << setprecision(24) << (double)sum / (double)(n - k + 1) << endl;

    return 0;
}