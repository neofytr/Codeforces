#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX 5000

int arr[MAX + 1];

void solve() {
    int n, k;
    cin >> n >> k;

    vector<int> arr(n + 1, 0);
    vector<pair<int, int>> s;
    for (int r = 1; r <= n; r++)
        cin >> arr[r], s.push_back({arr[r], r});

    int sum = 0;
    sort(s.rbegin(), s.rend());
    vector<int> idx;
    for (int r = 0; r < k; r++)
        idx.push_back(s[r].second), sum += s[r].first;

    int j = 0, maxi = LLONG_MIN;
    sort(idx.begin(), idx.end());

    int start = 1;
    if (idx[0] == 1) start = 2 , j = 1;
    while (start <= n) {
        int end = start;
        while (end <= n && end < idx[j]) end++;
        if (start != idx[j]) maxi = max(maxi, arr[start]);
        if (end != start) maxi = max(maxi, arr[end]);

        start = idx[j] + 1;
        j++;
    }

    cout << maxi + sum << endl;
}

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}