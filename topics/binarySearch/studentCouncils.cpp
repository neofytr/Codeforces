#include <bits/stdc++.h>
using namespace std;

bool func(const vector<long long> &arr, long long num, int k) {
    long long total = 0;
    for (const long long &val: arr) {
        total += min(val, num);
    }
    return total >= num * k;
}

int main() {
    int k, n;
    cin >> k >> n;

    vector<long long> arr(n);
    for (long long &val: arr) {
        cin >> val;
    }

    long long left = 0;
    long long right = 1e10;

    while (right != left + 1) {
        long long mid = left + (right - left) / 2;
        if (func(arr, mid, k)) {
            left = mid;
        } else {
            right = mid;
        }
    }

    cout << left << endl;
    return 0;
}
