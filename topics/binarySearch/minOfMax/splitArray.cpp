#include <bits/stdc++.h>
using namespace std;

bool canDivide(vector<long long> &a, int k, long long maxSum) {
    int count = 1;
    long long currentSum = 0;

    for (auto x: a) {
        if (currentSum + x <= maxSum) {
            currentSum += x;
        } else {
            count++;
            currentSum = x;
        }
    }

    return count <= k;
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<long long> a(n);

    for (auto &x: a) {
        cin >> x;
    }

    long long left = *max_element(a.begin(), a.end());
    long long right = accumulate(a.begin(), a.end(), 0LL);

    while (left < right) {
        long long mid = left + (right - left) / 2;

        if (canDivide(a, k, mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    cout << left << endl;
}
