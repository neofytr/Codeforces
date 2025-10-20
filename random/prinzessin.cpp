#include <bits/stdc++.h>
using namespace std;

#define int long long

// generating the next string in lexicographic order is equivalent to
// adding 1 in base 26
void next(string &str) {
    int n = (int)str.length();
    int r = n - 1;
    while (r >= 0 && str[r] == 'z') // these will generate a carry when 1 is added
        str[r] = 'a', r--;

    if (r >= 0)
        str[r]++; // increment the first non carry generating character
    else
        str = string(n + 1, 'a'); // if everything is a z
}

void solve() {
    int n;
    cin >> n;

    string str;
    cin >> str;

    string lex = "a";
    set<string> s;
    for (int l = 1; l <= n; l++) {
        for (int r = 0; r <= n - l; r++)
            s.insert(str.substr(r, l));
        int d = lex.length();
        while (lex.length() == d) {
            if (!s.contains(lex)) {
                cout << lex << endl;
                return;
            } else
                next(lex);
        }
    }
    return;
}

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}