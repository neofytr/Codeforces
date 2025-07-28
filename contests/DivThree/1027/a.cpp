#include <bits/stdc++.h>
using namespace std;

#define getDig(x) ((x) - '0')

void solve() {
    string str;
    cin >> str;

    int num = getDig(str[0]) * 1000 + 100 * getDig(str[1]) + 10 * getDig(str[2]) + 1 * getDig(str[3]);
    int squareRoot = (int)sqrt(num);
    if (squareRoot * squareRoot < num) {
        cout << -1 << endl;
    } else {
        cout << 0 << " " << squareRoot << endl;
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