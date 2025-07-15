#include <bits/stdc++.h>
using namespace std;

bool canPlaceCows(const vector<long long> &stalls, const int k, const long long distance) {
    int count = 1; // place first cow in the first stall
    long long last = stalls[0];

    for (int i = 1; i < stalls.size(); i++) {
        if (stalls[i] - last >= distance) {
            count++;
            last = stalls[i];
        }
    }

    return count >= k;
}

int main() {
    int n, k;
    cin >> n >> k;

    vector<long long> stalls(n);
    for (long long &val: stalls) {
        cin >> val;
    }

    // we maintain the invariant stalls[left] is true and stalls[right] is false

    long long left = 0;
    long long right = stalls[n - 1] - stalls[0] + 1;

    while (right != left + 1) {
        const long long mid = left + (right - left) / 2;
        if (canPlaceCows(stalls, k, mid)) {
            left = mid;
        } else {
            right = mid;
        }
    }

    cout << left << endl;
    return EXIT_SUCCESS;
}
