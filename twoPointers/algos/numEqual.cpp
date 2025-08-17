#include <bits/stdc++.h>
#include <vector>
using namespace std;

#define int long long

int32_t main() {
    int n, m;
    cin >> n >> m;

    vector<int> A(n), B(m);
    for (int &val : A)
        cin >> val;
    for (int &val : B)
        cin >> val;

    // A and B are sorted in non-decreasing order
    // We are to find the number of pairs (i, j) for which A[i] == B[j]
    int cnt = 0;
    int i = 0, j = 0;
    while (i < n && j < m) {
        if (A[i] < B[j]) {
            i++;
            continue;
        }

        int startI = i;
        while (i < n && A[i] == B[j])
            i++;
        int startJ = j;
        while (j < m && B[j] == B[startJ])
            j++;
        cnt += (i - startI) * (j - startJ);
    }

    cout << cnt << endl;
    return EXIT_SUCCESS;
}