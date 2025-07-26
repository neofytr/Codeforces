#include <bits/stdc++.h>
#include <vector>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;

    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    int left = 0;
    int right = 0;
    int currLen = 0;
    int count = 0;

    while (right < n) {
        while (left < n && arr[left]) {
            left++;
        }
        bool hasToBreak = false;

        right = left;

        while (right < n && !arr[right]) {
            right++;
            currLen++;
            if (currLen == k) {
                hasToBreak = true;
                count++;
                break;
            }
        }

        currLen = 0;
        if (hasToBreak) {
            right++;
        }

        left = right;
    }

    cout << count << endl;
    return;
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
}