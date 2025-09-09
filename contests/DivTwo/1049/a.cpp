#include <iostream>
#include <string>
using namespace std;

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;

    int zero_count = 0;
    for (char c : s) {
        if (c == '0') {
            zero_count++;
        }
    }

    if (zero_count == 0 || zero_count == n) {
        cout << 0 << endl;
        return;
    }

    int misplaced_ones = 0;
    for (int i = 0; i < zero_count; ++i) {
        if (s[i] == '1') {
            misplaced_ones++;
        }
    }

    cout << misplaced_ones << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
