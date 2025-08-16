#include <bits/stdc++.h>
#include <cstdlib>
using namespace std;

int main() {
    string str;
    cin >> str;
    if (str == "red")
        cout << "SSS\n";
    else if (str == "blue")
        cout << "FFF\n";
    else if (str == "green")
        cout << "MMM\n";
    else
        cout << "Unknown\n";

    return EXIT_SUCCESS;
}