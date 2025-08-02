#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    int zeroCount = 0;
    int oneCount = 0;
    int score = 0;
    while (n--) {
        int a;
        cin >> a;
        if (!a)
            zeroCount++;
        else if (a == 1)
            oneCount++;
        else
            score += a; // it will anyway be added to score via sum
    }

    if (zeroCount > oneCount) {
        score += (oneCount) * 2;             // mex{0, 1}
        score += (zeroCount - oneCount) * 1; // mex{0}
    } else {
        score += (zeroCount) * 2;            // mex {0, 1}
        score += (oneCount - zeroCount) * 1; // sum {1}
    }

    cout << score << endl;
    return;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}