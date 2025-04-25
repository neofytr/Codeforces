#include <bits/stdc++.h>
using namespace std;


bool binary_search(vector<long long> &arr, long long target) {
    long long left = 0;
    long long right = arr.size() - 1;
    long long mid;
    while (left <= right) {
        mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            return true;
        } else if (arr[mid] > target) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return false;
}

int main() {
    int n, k;
    cin >> n >> k;

    vector<long long> arr(n);
    for (long long &val: arr) {
        cin >> val;
    }

    long long query;
    while (k--) {
        cin >> query;
        if (binary_search(arr, query)) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return EXIT_SUCCESS;
}
