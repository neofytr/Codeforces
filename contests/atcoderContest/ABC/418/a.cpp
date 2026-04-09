#include <bits/stdc++.h>
#include <cstdlib>
using namespace std;

int main() {
    int n;
    cin >> n;
    string str;
    cin >> str;

    if (n < 3) {
        cout << "No\n";
        return EXIT_SUCCESS;
    }

    int last = n - 1;
    int secondLast = n - 2;
    int thirdLast = n - 3;

    if (str[thirdLast] == 't' && str[secondLast] == 'e' && str[last] == 'a') {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
    return EXIT_SUCCESS;
}