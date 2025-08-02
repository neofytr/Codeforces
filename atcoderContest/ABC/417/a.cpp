#include <bits/stdc++.h>
#include <cstdlib>
using namespace std;

int main() {
    int n, a, b;
    cin >> n >> a >> b;
    string str;
    cin >> str;

    string newStr;
    newStr.resize(n - (a + b));
    int index = 0;
    for (int i = a; i < n - b; i++) {
        newStr[index++] = str[i];
    }

    cout << newStr << endl;
    return EXIT_SUCCESS;
}