#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, target;
    cin >> n >> target;
    vector<int> arr(n);
    for (int &val: arr) {
        cin >> val;
    }

    vector<int> dp(target + 1, 0);
    dp[0] = 1;
    for (int sum = 1; sum <= target; sum++) {
        for (int index = 0; index < n; index++) {
            dp[sum] += (sum - arr[index] >= 0 ? dp[sum - arr[index]] : 0);
        }
    }

    vector<int> dpTwo(target + 1, 0);
    dpTwo[0] = 1;
    for (int sum = 0; sum <= target; sum++) {
        for (int index = 0; index < n; index++) {
            if (sum + arr[index] <= target) {
                dpTwo[sum + arr[index]] += dpTwo[sum];
            }
        }
    }

    cout << dp[target] << endl;
    cout << dpTwo[target] << endl;
    return EXIT_SUCCESS;
}
