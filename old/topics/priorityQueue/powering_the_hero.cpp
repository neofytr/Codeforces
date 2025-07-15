#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    priority_queue<long long> bonus;
    long long total_power = 0;

    long long card;
    for (int index = 0; index < n; index++) {
        cin >> card;
        if (!card) {
            // hero card
            if (!bonus.empty()) {
                total_power += bonus.top();
                bonus.pop();
            }
        } else {
            bonus.push(card);
        }
    }

    cout << total_power << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return EXIT_SUCCESS;
}
