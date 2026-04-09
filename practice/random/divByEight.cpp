#include <bits/stdc++.h>
using namespace std;

#define int long long 

int32_t main() {
    string num;
    cin >> num;

    for (char c : num) {
        if (c == '0') {
            cout << "YES\n0\n";
            return 0;
        }
        if (c == '8') {
            cout << "YES\n8\n";
            return 0;
        }
    }

    for (int r = 16; r <= 100; r += 8) {
        int ones = r % 10;
        int tens = (r / 10) % 10;

        bool foundTens = false, foundOnes = false;
        for (char c : num) {
            int n = c - '0';
            if (!foundTens && n == tens)
                foundTens = true;
            else if (foundTens && !foundOnes && n == ones)
                foundOnes = true;
            if (foundTens && foundOnes) {
                cout << "YES\n" << r << "\n";
                return 0;
            }
        }
    }

    for (int r = 104; r <= 992; r += 8) {
        int ones = r % 10;
        int tens = (r / 10) % 10;
        int hundreds = (r / 100) % 10;

        bool foundHundreds = false, foundTens = false, foundOnes = false;
        for (char c : num) {
            int n = c - '0';
            if (!foundHundreds && n == hundreds)
                foundHundreds = true;
            else if (foundHundreds && !foundTens && n == tens)
                foundTens = true;
            else if (foundTens && !foundOnes && n == ones)
                foundOnes = true;
            if (foundHundreds && foundTens && foundOnes) {
                cout << "YES\n" << r << "\n";
                return 0;
            }
        }
    }

    cout << "NO\n";
    return 0;
}
