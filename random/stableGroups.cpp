#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    int n, k, x;
    cin >> n >> k >> x;

    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    sort(arr.begin(), arr.end());

    vector<pair<int, int>> stable;
    int i = 0;
    while (i < n) {
        int j = i;
        while (j + 1 < n && arr[j + 1] - arr[j] <= x)
            j++;
        stable.push_back({arr[i], arr[j]});
        i = j + 1;
    }

    if (!k) {
        cout << stable.size() << endl;
        return 0;
    }

    int sz = stable.size();
    if (sz == 1) {
        cout << 1 << endl;
        return 0;
    }

    vector<int> needed;
    for (int r = 0; r < sz - 1; r++) {
        int lf = stable[r].second;
        int rt = stable[r + 1].first;
        int gap = rt - lf;

        int d = (gap - 1) / x;
        needed.push_back(d);
    }

    sort(needed.begin(), needed.end());

    int groups = sz;
    for (int d : needed) {
        if (k >= d) {
            k -= d;
            groups--; // merged
        } else break;
    }

    cout << groups << endl;
    return 0;
}
