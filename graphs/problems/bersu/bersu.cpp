#include <bits/stdc++.h>
#include <vector>
using namespace std;

// Problem: bersu
// URL: https://codeforces.com/problemset/problem/489/B
// Difficulty: medium
// Tags:
// Strategy:

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> boys(n);
    for (int &val : boys)
        cin >> val;
    int m;
    cin >> m;
    vector<int> girls(m);
    for (int &val : girls)
        cin >> val;

    sort(boys.begin(), boys.end());
    sort(girls.begin(), girls.end());

    int boy = 0;
    int girl = 0;
    int pair = 0;
    while (boy < n && girl < m) {
        if (abs(boys[boy] - girls[girl]) <= 1) {
            pair++;
            boy++;
            girl++;
            continue;
        }

        if (boys[boy] > girls[girl]) {
            // to make a pair, we need to move the girl pointer forward
            girl++;
        } else {
            boy++;
        }
    }
    cout << pair << endl;
    return 0;
}