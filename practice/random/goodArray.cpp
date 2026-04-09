#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    int n;
    cin >> n;

    vector<int> arr(n + 1);
    unordered_map<int, set<int>> mp;
    for (int r = 1; r <= n; r++)
        cin >> arr[r], mp[arr[r]].insert(r);

    vector<int> res;
    const int sum = accumulate(arr.begin(), arr.end(), 0LL);
    for (int j = 1; j <= n; j++) {
        int target = sum - arr[j];
        if (target & 1)
            continue;
        set<int> &s = mp[target / 2];

        if (s.size() == 1 && !s.contains(j))
            res.push_back(j);
        if (s.size() > 1)
            res.push_back(j);
    }

    cout << res.size() << endl;
    for (int r : res)
        cout << r << " ";
    cout << endl;
    return 0;
}