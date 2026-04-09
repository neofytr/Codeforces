#include <bits/stdc++.h>
#include <cstdlib>
using namespace std;

int main() {
    string str;
    cin >> str;
    int n = (int)str.size();

    string t;
    t.resize(n);
    bool foundHash = true;
    for (int index = 0; index < n; index++) {
        if (str[index] == '#') {
            t[index] = '#';
            foundHash = true;
            continue;
        }

        if (foundHash && str[index] == '.') {
            t[index] = 'o';
            foundHash = false;
            continue;
        }

        t[index] = str[index];
    }

    cout << t << endl;
    return EXIT_SUCCESS;
}