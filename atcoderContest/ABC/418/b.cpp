#include <bits/stdc++.h>
#include <cstdlib>
using namespace std;

int main() {
    string str;
    cin >> str;

    int n = (int)str.length();
    int left = 0;
    int right = 0;
    double fillingRate = 0;

    while (left < n && right < n) {
        while (left < n && str[left] != 't')
            left++;

        int last = -1;
        while (right < n) {
            if (str[right] == 't')
                last = right;
            right++;
        }

        if (last == -1)
            break;

        right = last;
        fillingRate = fmax(fillingRate, ())
    }

    cout << fillingRate << endl;
    return EXIT_SUCCESS;
}