#include <bits/stdc++.h>
using namespace std;
// https://codeforces.com/problemset/problem/550/A
int main() {
    string s;
    cin >> s;

    if (s.find("AB") != string::npos && s.find("BA", s.find("AB") + 2) != string::npos)
        cout << "YES\n";
    else if (s.find("BA") != string::npos && s.find("AB", s.find("BA") + 2) != string::npos)
        cout << "YES\n";
    else
        cout << "NO\n";
}
