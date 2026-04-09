#include <bits/stdc++.h>
#include <cstdlib>
using namespace std;

int main() {
    int n, l, r;
    cin >> n >> l >> r;
    l--, r--;
    string str;
    cin >> str;

    for (int index = l; index <= r; index++) {
        if (str[index] != 'o') {
            cout << "No\n";
            return EXIT_SUCCESS;
        }
    }

    cout << "Yes\n";
    return EXIT_SUCCESS;
}