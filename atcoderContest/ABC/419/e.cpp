#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, L;
    cin >> N >> M >> L;

    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }

    vector<int> increases(N, 0);

    for (int start = 0; start <= N - L; start++) {
        int sum = 0;
        for (int j = start; j < start + L; j++) {
            sum += A[j] + increases[j];
        }

        int remainder = sum % M;
        if (remainder != 0) {
            int needed = M - remainder;
            increases[start + L - 1] += needed;
        }
    }

    int total = 0;
    for (int i = 0; i < N; i++) {
        total += increases[i];
    }

    if (total == 0) {
        cout << "O" << endl;
    } else {
        cout << total << endl;
    }

    return 0;
}