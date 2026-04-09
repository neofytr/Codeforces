#include <bits/stdc++.h>
#include <cstdlib>
#include <vector>
using namespace std;

#define int long long

int32_t main() {
    int n, m;
    cin >> n >> m;

    vector<int> a(n);
    vector<int> b(m);
    for (int &val : a)
        cin >> val;
    for (int &val : b)
        cin >> val;

    vector<bool> done(n, false);
    for (int op = 0; op < m; op++) {
        int left = -1; // a[left] < b[op]
        int right = n; // a[right] >= b[op]

        while (right != left + 1) {
            int mid = left + (right - left) / 2;
            if (a[mid] >= b[op]) {
                right = mid;
            } else {
                left = mid;
            }
        }

        if (right != n) {
            // this means that there is an element b[op] in the array A
            while (done[right])
                right++;

            if (a[right] == b[op])
                done[right] = true;
        }
    }

    for (int index = 0; index < n; index++) {
        if (!done[index])
            cout << a[index] << " ";
    }
    cout << endl;
    return EXIT_SUCCESS;
}