#include <bits/stdc++.h>
#include <cstdlib>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> A(n), B(m);
    for (int &val : A)
        cin >> val;
    for (int &val : B)
        cin >> val;

    // we want to calculate for each element b[r], the number of elements a[k] such that a[k] < b[r]
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());

    int k = 0;
    int r = 0;
    vector<int> ans(m, 0);
    while (r < m) {
        while (k < n && A[k] < B[r])
            k++;
        ans[r++] = k;
    }

    for (int i = 0; i < m; i++)
        cout << B[i] << " -> " << ans[i] << endl;
    return EXIT_SUCCESS;
}