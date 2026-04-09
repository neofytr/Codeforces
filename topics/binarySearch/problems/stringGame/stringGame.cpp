#include <bits/stdc++.h>
#include <vector>
using namespace std;

#define int long long

// Problem: stringGame
// URL: https://codeforces.com/edu/course/2/lesson/6/2/practice/contest/283932/problem/F
// Difficulty: medium
// Tags:
// Strategy:

bool can(int x, string &t, string &p, vector<int> &perm) {
    string cp = t;
    for (int i = 0; i < x; i++) {
        int index = perm[i] - 1;
        cp[index] = -1;
    }

    int pindex = 0;
    int tindex = 0;
    while (pindex < p.size() && tindex < cp.size()) {
        if (cp[tindex] == -1) {
            tindex++;
            continue;
        }

        if (cp[tindex] == p[pindex]) {
            pindex++;
            tindex++;
        } else {
            tindex++;
        }
    }

    if (pindex == p.size())
        return true;

    return false;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string t, p;
    cin >> t >> p;

    vector<int> perm(t.size());
    for (int &val : perm)
        cin >> val;

    // if he can't delete x words, then he can't delete x + 1

    int left = 0;             // if he doesn't delete anything, he can make the word p since it's guaranteed to be made from t
    int right = t.size() + 1; // if he deletes everything, he can't make anything

    while (right != left + 1) {
        int mid = left + (right - left) / 2;
        if (can(mid, t, p, perm))
            left = mid;
        else
            right = mid;
    }

    cout << left << endl;

    return 0;
}