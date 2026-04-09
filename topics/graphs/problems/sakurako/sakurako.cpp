#include <bits/stdc++.h>
#include <vector>
using namespace std;

// Problem: sakurako
// URL: https://codeforces.com/problemset/problem/2008/D
// Difficulty: medium
// Tags:
// Strategy:

#define WHITE '1'
#define BLACK '0'

void solve() {
    int n;
    cin >> n;

    vector<int> arr(n + 1);
    for (int index = 1; index <= n; index++)
        cin >> arr[index];

    string str;
    cin >> str;
    vector<bool> isBlack(n + 1, 1);
    for (int index = 1; index <= n; index++) {
        if (str[index - 1] == WHITE) {
            isBlack[index] = 0;
        }
    }

    // dp approach didn't work in this since in a cycle, all the elements will have the same
    // answer value but dp will build incrementally which will not be correct
    vector<int> ans(n + 1);
    vector<bool> visited(n + 1, false);
    for (int node = 1; node <= n; node++) {
        vector<int> cycle;
        int s = node;
        int count = 0;
        while (!visited[s]) {
            visited[s] = true;
            if (isBlack[s])
                count++;
            s = arr[s];
            cycle.push_back(s);
        }

        // all the elements in the cycle have the same value
        for (int x : cycle)
            ans[x] = count;
    }

    for (int node = 1; node <= n; node++)
        cout << ans[node] << " ";
    cout << endl;
    return;
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