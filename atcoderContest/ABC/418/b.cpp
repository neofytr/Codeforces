#include <bits/stdc++.h>
#include <cstdlib>
using namespace std;

#define int long long

double search(int left, int right, string &str) {
    if (left == -1 || right == -1)
        return 0;
    if (left > right)
        return 0;
    if (right - left + 1 < 3)
        return 0;
    int n = (int)str.length();

    int count = 0;
    for (int index = left; index <= right; index++) {
        if (str[index] == 't')
            count++;
    }

    int next = -1;
    for (int index = left + 1; index <= right; index++) {
        if (str[index] == 't') {
            next = index;
            break;
        }
    }

    int last = -1;
    for (int index = right - 1; index >= left; index--) {
        if (str[index] == 't') {
            last = index;
            break;
        }
    }

    double rate = ((double)count - 2) / (double)(right - left + 1 - 2);
    return fmax(rate, fmax(search(next, right, str), search(left, last, str)));
}

int32_t main() {
    string str;
    cin >> str;

    int next = -1;
    for (int index = 0; index < str.length(); index++) {
        if (str[index] == 't') {
            next = index;
            break;
        }
    }

    int last = -1;
    for (int index = str.length() - 1; index >= 0; index--) {
        if (str[index] == 't') {
            last = index;
            break;
        }
    }

    cout << setprecision(24) << search(next, last, str) << endl;

    return EXIT_SUCCESS;
}