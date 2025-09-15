#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

void solve() {
    int size;
    cin >> size;
    vector<int> nums(size);
    vector<long long> sums(size + 1, 0);

    for (int i = 0; i < size; ++i) {
        cin >> nums[i];
        sums[i + 1] = sums[i] + nums[i];
    }

    for (int i = 1; i <= size - 2; ++i) {
        for (int j = i + 1; j <= size - 1; ++j) {
            long long part1 = sums[i];
            long long part2 = sums[j] - sums[i];
            long long part3 = sums[size] - sums[j];

            int rem1 = part1 % 3;
            int rem2 = part2 % 3;
            int rem3 = part3 % 3;

            bool same = (rem1 == rem2 && rem2 == rem3);
            bool diff = (rem1 != rem2 && rem1 != rem3 && rem2 != rem3);

            if (same || diff) {
                cout << i << " " << j << endl;
                return;
            }
        }
    }
    cout << "0 0" << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int testCases;
    cin >> testCases;
    while (testCases--) {
        solve();
    }
    return 0;
}
