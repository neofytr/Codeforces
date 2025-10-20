#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;

        int zeros = count(s.begin(), s.end(), '0');
        bool mid = (n % 2 == 1 && s[n/2] == '0');

        if (zeros == 1) {
            cout << "BOB\n";
        } else if ((zeros % 2 == 1) && mid) {
            cout << "ALICE\n";
        } else {
            cout << "BOB\n";
        }
    }
    return 0;
}
