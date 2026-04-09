#include <bits/stdc++.h>
using namespace std;

int main() {
    string str;
    cin >> str;

    set<char> vowel = {'a', 'o', 'y', 'e', 'u', 'i', 'A', 'O', 'Y', 'E', 'U', 'I'};
    string res;

    for (char c : str) {
        if (!vowel.count(c)) {
            res.push_back('.');
            res.push_back(tolower(c));
        }
    }

    cout << res << endl;
    return 0;
}
