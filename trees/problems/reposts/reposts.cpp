#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: reposts
// URL: https://codeforces.com/problemset/problem/522/A
// Difficulty: medium
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    int chainLen = 1;
    string last = "polycarp";

    while (n--) {
        string name1, repost, name2;
        cin >> name1 >> repost >> name2;

        if (name2.size() != last.size())
            continue;

        int sz = name2.size();
        bool isSame = true;
        for (int r = 0; r < sz; r++)
            if (tolower(name2[r]) != tolower(last[r]))
                isSame = false;
        if (isSame)
            chainLen++, last = name1;
    }
    cout << chainLen << endl;
    return 0;
}