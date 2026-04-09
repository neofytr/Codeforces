#include <bits/stdc++.h>
#include <cstdlib>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> A(n);
    vector<int> B(m);

    for (int &val : A)
        cin >> val;
    for (int &val : B)
        cin >> val;

    // A and B are sorted in non-decreasing order
    vector<int> C(n + m);

    int i = 0, j = 0, k = 0;
    while (i < n && j < m) {
        if (A[i] < B[j]) {
            C[k++] = A[i++];
        } else {
            C[k++] = B[j++];
        }
    }

    while (i < n)
        C[k++] = A[i++];
    while (j < m)
        C[k++] = B[j++];

    for (int val : C)
        cout << val << " ";
    cout << endl;
    return EXIT_SUCCESS;
}