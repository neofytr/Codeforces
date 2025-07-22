// https://codeforces.com/gym/317667/problem/A

#include <bits/stdc++.h>
#include <cstdlib>
#include <vector>
using namespace std;

int main() {
    int n, t;
    cin >> n >> t;

    vector<int> arr(n + 1, 0);
    for (int index = 1; index <= n - 1; index++) {
        cin >> arr[index];
    }

    int pos = 1;
    while (true) {
        if (pos == t) {
            cout << "YES\n";
            return EXIT_SUCCESS;
        }

        if (pos == n)
            break;
        pos += arr[pos];
    }

    cout << "NO\n";
    return EXIT_SUCCESS;
}