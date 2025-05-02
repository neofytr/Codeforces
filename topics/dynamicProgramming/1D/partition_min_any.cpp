#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> arr(n);
    for (long long &val: arr) {
        cin >> val;
    }

    // we want to partition arr into two subsets such that
    // the absolute value of the difference between the sum
    // of the values in the subsets is the minimum

    const long long total = accumulate(arr.begin(), arr.end(), 0LL);
    vector<bool> dp(total / 2);
    // dp[r] indicates if we can make sum r using a subset of arr

    // base case
    dp[0] = true;

    for (const long long num: arr) {
        for (long long sum = total / 2; sum >= num; sum--) {
            dp[sum] = dp[sum] || dp[sum - num];
        }
    }

    long long minimum = LONG_LONG_MAX;
    for (long long sum = 0; sum <= total / 2; sum++) {
        if (dp[sum]) {
            // if we can make this sum using a subset, check if we can get a minimum partition
            // the first sum is 'sum' itself
            // the second sum is total - sum
            minimum = min(minimum, abs(2 * sum - total));
        }
    }

    cout << minimum << endl;
    return EXIT_SUCCESS;
}
