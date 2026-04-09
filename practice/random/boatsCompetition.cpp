// https://codeforces.com/problemset/problem/1399/C

#include <bits/stdc++.h>
using namespace std;

#define int long long
int32_t main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> arr(n);
        for (int &val : arr)
            cin >> val;
        sort(arr.begin(), arr.end());

        if (n == 1) {
            cout << 0 << endl;
            continue;
        }

        int minTeamSum = arr[0] + arr[1];
        int maxTeamSum = arr[n - 1] + arr[n - 2];
        int maxCount = 0;
        for (int sum = minTeamSum; sum <= maxTeamSum; sum++) {
            int count = 0;
            vector<bool> used(n, false);
            for (int i = 0; i < n; i++) {
                // find j > i such that a[i] + a[j] = sum
                if (!used[i]) {
                    int target = sum - arr[i];
                    auto itr = lower_bound(arr.begin() + i + 1, arr.end(), target);
                    if (itr == arr.end())
                        continue;
                    int elt = *itr;
                    if (*itr != target)
                        continue;
                    int index = itr - arr.begin();
                    while (index < n && arr[index] == *itr && used[index])
                        index++;
                    if (index < n && arr[index] == *itr) {
                        used[index] = true;
                        count++;
                    }
                }
            }
            maxCount = max(maxCount, count);
        }
        cout << maxCount << endl;
    }
    return 0;
}