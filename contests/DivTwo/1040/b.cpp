#include <bits/stdc++.h>
#include <vector>
using namespace std;

void solve() {
    int n, s;
    cin >> n >> s;
    vector<int> arr(n);
    int minSum = 0;
    for (int &val : arr) {
        cin >> val;
        minSum += val;
    }

    if (s <= minSum) {
        cout << -1 << endl;
        return;
    }

    
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
}