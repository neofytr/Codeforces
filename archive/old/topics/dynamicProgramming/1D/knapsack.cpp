#include <bits/stdc++.h>
using namespace std;

#define MAX_TARGET 100000

int main() {
    int n, target;
    cin >> n >> target;
    vector<int> arr(n);
    for (int &val: arr) {
        cin >> val;
    }

    bitset<MAX_TARGET + 1> dp;
    // dp[i] denotes if the sum i can be reached

    dp.set(0); // sum zero can be reached (by not taking any element from the set); base case

    // we have to check if it's possible to select some elements from arr such that they sum to T
    for (int index = 0; index < n; index++) {
        dp |= (dp >> arr[index]);
    }

    if (dp[target]) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }

    return EXIT_SUCCESS;
}
