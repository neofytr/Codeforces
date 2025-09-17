#include <bits/stdc++.h>
using namespace std;

void solve() {
    int size;
    cin >> size;
    vector<int> arr(size);
    int peakIndex = -1;

    for (int i = 0; i < size; ++i) {
        cin >> arr[i];
        if (arr[i] == size) {
            peakIndex = i;
        }
    }

    bool valid = true;

    for (int i = 0; i < peakIndex - 1; ++i) {
        if (arr[i] > arr[i + 1]) {
            valid = false;
            break;
        }
    }

    if (valid) {
        for (int i = peakIndex; i < size - 1; ++i) {
            if (arr[i] < arr[i + 1]) {
                valid = false;
                break;
            }
        }
    }

    cout << (valid ? "YES" : "NO") << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int testCases;
    cin >> testCases;
    while (testCases--) {
        solve();
    }

    return 0;
}
