#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n;
    cin >> n;

    vector<int> arr(n + 1);
    for (int r = 1; r <= n; r++)
        cin >> arr[r];

    vector<int> res;
    int i = 1, j = 1;
    while (i <= n) {
        j = i;
        int j1 = j, j2 = j;
        while (j1 < n && arr[j1 + 1] > arr[j1])
            j1++;
        while (j2 < n && arr[j2 + 1] < arr[j2])
            j2++;

        int l1 = j1 - j + 1;
        int l2 = j2 - j + 1;

        if (l2 == 1 && l1 == 1)
            break;

        if (l1 >= 2) {
            res.push_back(arr[i]);
            res.push_back(arr[j1]);
            i = j1;
            continue;
        }
        if (l2 >= 2) {
            res.push_back(arr[i]);
            res.push_back(arr[j2]);
            i = j2;
        }
    }

    unordered_map<int, int> mp;
    for (int r : res)
        mp[r]++;

    cout << mp.size() << endl;

    i = 0;
    while (i < res.size()) {
        cout << res[i] << " ";
        while (i < res.size() - 1 && res[i] == res[i + 1])
            i++;
        i++;
    }
    cout << endl;
}

int32_t main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}