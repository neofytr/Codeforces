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

    int longestChain = 0;
    unordered_map<string, int> chain;

    chain["polycarp"] = 1;
    while (n--) {
        string name1, reposted, name2;
        cin >> name1 >> reposted >> name2;

        string modifiedOne = name1;
        for (int r = 0; r < modifiedOne.size(); r++)
            modifiedOne[r] = tolower(modifiedOne[r]);
        string modifiedTwo = name2;
        for (int r = 0; r < modifiedTwo.size(); r++)
            modifiedTwo[r] = tolower(modifiedTwo[r]);

        chain[modifiedOne] = chain[modifiedTwo] + 1;
        longestChain = max(longestChain, chain[modifiedOne]);
    }
    cout << longestChain << endl;
    return 0;
}