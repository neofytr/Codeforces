#include <bits/stdc++.h>
#include <cstdlib>
#include <vector>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> A(n);
    vector<int> B(n);

    for (int &val : A) {
        cin >> val;
    }
    for (int &val : B) {
        cin >> val;
    }

    int iter = 1;
    for (int index = 0; index < n; index++) {
        if (A[index] > B[index]) {
            iter += (A[index] - B[index]);
        }
    }

    cout << iter << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return EXIT_SUCCESS;
}