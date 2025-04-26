#include <bits/stdc++.h>
using namespace std;

bool func(const vector<int> &arr, const string &t, const string &p, const int index) {
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

    int left = -1, right = t_len;
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
