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

        if (n == 1) {
            cout << "YES\n";
            continue;
        }

        int yasser = accumulate(arr.begin(), arr.end(), 0LL);

        // dpFront[r] = max subarray sum ending at r
        vector<int> dpFront(n);
        dpFront[0] = arr[0];
        int maxiFront = dpFront[0];
        for (int r = 1; r < n - 1; r++) {
            dpFront[r] = max(dpFront[r - 1] + arr[r], arr[r]);
            maxiFront = max(maxiFront, dpFront[r]);
        }

        // dpBack[r] = max subarray sum ending at r (starting from index >=1)
        vector<int> dpBack(n);
        dpBack[1] = arr[1];
        int maxiBack = dpBack[1];
        for (int r = 2; r < n; r++) {
            dpBack[r] = max(dpBack[r - 1] + arr[r], arr[r]);
            maxiBack = max(maxiBack, dpBack[r]);
        }

        int totalMax = max(maxiBack, maxiFront);
        if (totalMax < yasser)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
    return 0;
}
