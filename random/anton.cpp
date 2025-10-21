#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    int n;
    cin >> n;

    string str;
    cin >> str;

    int anton = count(str.begin(), str.end(), 'A');
    int danik = count(str.begin(), str.end(), 'D');

    if (anton == danik)
        cout << "Friendship\n";
    else if (anton > danik)
        cout << "Anton\n";
    else
        cout << "Danik\n";
    return 0;
}