#include <bits/stdc++.h>
using namespace std;

bool func(const vector<int> &arr, const string &t, const string &p, const int index) {
    if (index <= -1) {
        return true;
    } else if (index >= t.size()) {
        return false;
    }

    vector<bool> deleted(t.length(), false);
    for (int i = 0; i <= index; i++) {
        deleted[arr[i]] = true;
    }

    int j = 0;
    for (int i = 0; i < t.length() && j < p.length(); i++) {
        if (!deleted[i] && t[i] == p[j]) {
            j++;
        }
    }

    return j == p.length();
}

int main() {
    string t, p;
    cin >> t >> p;

    int t_len = t.length();

    vector<int> arr(t_len);
    for (int i = 0; i < t_len; i++) {
        cin >> arr[i];
        arr[i]--;
    }

    // if index is such that element deleting elements arr[0], ..., arr[index] from t, we cannot generate p from t, then
    // the same is true for position index + 1, for all but the last position

    // we are to find the largest index upto which the above is not true

    // we maintain the invariant that func(left) is true and func(right) is false
    int left = -1, right = t_len; // artificial elements
    while (right > left + 1) {
        int mid = left + (right - left) / 2;
        if (func(arr, t, p, mid)) {
            left = mid;
        } else {
            right = mid;
        }
    }

    // left is the maximum index for which we can delete letters and still form p
    cout << left + 1 << endl;

    return 0;
}
