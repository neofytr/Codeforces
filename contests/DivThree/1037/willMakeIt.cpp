#include <algorithm>
#include <bits/stdc++.h>
#include <cstdlib>
#include <vector>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;

    // 1-based indexing
    vector<long long> tow(n + 1, -1);
    for (int index = 1; index <= n; index++) {
        cin >> tow[index];
    }

    // at time 0
    long long currTime = 0;
    long long timeToJump = 0;
    long long currTowerLevel = tow[k];
    long long currWaterLevel = 1;

    sort(tow.begin(), tow.end());
    long long maxLevel = tow[n];
    while (true) {
        if (currTowerLevel == maxLevel) {
            cout << "yes\n";
            return;
        }

        long long timeLeft = currTowerLevel - currWaterLevel + 1;
        if (timeLeft <= 0) {
            cout << "no\n";
            return;
        }

        auto itr = lower_bound(tow.begin(), tow.end(), timeLeft + currTowerLevel);
        if (itr == tow.end()) {
            cout << "no\n";
            return;
        }

        if (*itr > timeLeft + currTowerLevel) {
            cout << "no\n";
            return;
        }

        currWaterLevel += (timeLeft);
        currTowerLevel = *itr;
        currTime += timeLeft;
    }
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
}