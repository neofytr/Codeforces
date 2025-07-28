#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;

    string str;
    cin >> str;

    int zeroPalindromeCount = 0;
    int onePalindromeCount = 0;
    int notCount = 0;
    for (int index = 0; index < n / 2; index++) {
        if (str[index] == str[n - index - 1]) {
            if (str[index] == '0') {
                zeroPalindromeCount++;
            } else {
                onePalindromeCount++;
            }
        } else {
            notCount++;
        }
    }

    int total = zeroPalindromeCount + onePalindromeCount;
    if (total == k) {
        cout << "yes\n";
        return;
    }

    if (total < k) {
        // we can take any two non-palindromic pairs and swap in exactly one way to
        // get two palindromic pairs
        int canCreate = (notCount / 2) * 2;
        for (int r = 2; r <= canCreate; r += 2) {
            if (total + r == k) {
                cout << "yes\n";
                return;
            }
        }

        cout << "no\n";
    } else {
        // we can take a 0 and a 1 palindromic pair and swap them in exactly one way to
        // destroy two palindromic pairs
        int canDestroy = min(zeroPalindromeCount, onePalindromeCount) * 2;
        for (int r = 2; r <= canDestroy; r += 2) {
            if (total - r == k) {
                cout << "yes\n";
                return;
            }
        }
        cout << "no\n";
    }

    return;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}