#include <bits/stdc++.h>
using namespace std;

bool ask(const string &s) {
    cout << "? " << s << '\n';
    cout.flush();
    bool res;
    cin >> res;
    return res;
}

void submit(const string &s) {
    cout << "! " << s << '\n';
    cout.flush();
}

void solve() {
    int n;
    cin >> n;

    string cur = "";

    while ((int)cur.size() < n) {
        if (ask(cur + "0")) cur.push_back('0');
        else if (ask(cur + "1")) cur.push_back('1');
        else break;
    }

    while ((int)cur.size() < n) {
        if (ask("0" + cur)) cur = '0' + cur;
        else cur = '1' + cur;
    }

    submit(cur);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();
}
